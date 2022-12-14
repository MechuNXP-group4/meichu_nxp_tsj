/*
 * Copyright 2019-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "client.h"
#include "wlan_bt_fw.h"
#include "wlan.h"
#include "wifi.h"
#include "wm_net.h"
#include <wm_os.h>

#include "lwip/tcpip.h"

#include "fsl_adapter_gpio.h"
#include "fsl_common.h"

#include <math.h>

#include "display_support.h"
#include "camera_support.h"
#include "fsl_pxp.h"

#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "board.h"

//#include "timer.h"
#include "image.h"
#include "chgui.h"

// ----------------------------- WIFI DEFIN -----------------------------
#ifndef AP_SSID
#define AP_SSID "fridge_test"
#endif

#ifndef AP_PASSPHRASE
#define AP_PASSPHRASE "fridge12345678"
#endif

#ifndef PING_ADDR
#define PING_ADDR "8.8.8.8"
#endif

// ----------------------------- WIFI  TASK -----------------------------
const int wifi_PRIO       = OS_PRIO_4;
const int wifi_STACK_SIZE = 800;

portSTACK_TYPE *wifi_stack = NULL;
TaskHandle_t wifi_task_handler;
TaskHandle_t main_task_handler;

struct wlan_network sta_network;

static char firstResult             = 0;
static TaskHandle_t xInitTaskNotify = NULL;
static TaskHandle_t xJoinTaskNotify = NULL;

// ----------------------------- Bundle API -----------------------------
// Bundle includes.
#include "mobilenet_quant.h"
#include "glow_bundle_utils.h"

// Statically allocate memory for constant weights (model weights) and initialize.
GLOW_MEM_ALIGN(MOBILENET_QUANT_MEM_ALIGN)
uint8_t constantWeight[MOBILENET_QUANT_CONSTANT_MEM_SIZE] = {
#include "mobilenet_quant.weights.txt"
};

// Statically allocate memory for mutable weights (model input/output data).
GLOW_MEM_ALIGN(MOBILENET_QUANT_MEM_ALIGN)
uint8_t mutableWeight[MOBILENET_QUANT_MUTABLE_MEM_SIZE];

// Statically allocate memory for activations (model intermediate results).
GLOW_MEM_ALIGN(MOBILENET_QUANT_MEM_ALIGN)
uint8_t activations[MOBILENET_QUANT_ACTIVATIONS_MEM_SIZE];

// Bundle input data absolute address.
uint8_t *inputAddr = GLOW_GET_ADDR(mutableWeight, MOBILENET_QUANT_serving_default_mobilenetv2_0_50_160_input_0);

// Bundle output data absolute address.
uint8_t *outputAddr = GLOW_GET_ADDR(mutableWeight, MOBILENET_QUANT_StatefulPartitionedCall_0);

// ---------------------------- Application -----------------------------
// Model input size
#define IMAGE_CHANNELS              3
#define MODEL_INPUT_HEIGHT          160
#define MODEL_INPUT_WIDTH           160
#define MODEL_INPUT_SIZE            MODEL_INPUT_HEIGHT * MODEL_INPUT_WIDTH * IMAGE_CHANNELS

#define MODEL_COLOR_ORDER           RGB_COLOR_ORDER
#define MODEL_IMAGE_LAYOUT          NHWC_LAYOUT
#define MODEL_IMAGE_SCALE_MODE      SCALE_0TO1

// Number of output classes for the model.
#define MODEL_NUM_OUTPUT_CLASSES  4

// Allocate buffer for input data. This buffer contains the input image
// pre-processed and serialized as text to include here.
/*
uint8_t imageData[MODEL_INPUT_SIZE] = {
#include "input_image.inc"
};
*/

// Class labels.
const char* LABELS[MODEL_NUM_OUTPUT_CLASSES] = {
		"apple",
		"cabbage",
		"cucumber",
		"potato",
};

//Define size of pixels to extract from camera image. This will be scaled down later to fit model input
#define EXTRACT_HEIGHT  160
#define EXTRACT_WIDTH   160

//Calculate start of selection rectangle
int Rec_x = (480-EXTRACT_WIDTH)/2;
int Rec_y = (272-EXTRACT_HEIGHT)/2;

//#define DISPLAY_THRESHOLD 40

//uint8_t color_threshold = 140;
//bool display_threshold_reached=false;

/*******************************************************************************
 * CSI and LCD Definitions
 ******************************************************************************/
#define APP_FRAME_BUFFER_COUNT 4
/* Pixel format RGB565, bytesPerPixel is 2. */
#define APP_BPP 2

#if (FRAME_BUFFER_ALIGN > DEMO_CAMERA_BUFFER_ALIGN)
#define DEMO_FRAME_BUFFER_ALIGN FRAME_BUFFER_ALIGN
#else
#define CAMERA_FRAME_BUFFER_ALIGN DEMO_CAMERA_BUFFER_ALIGN
#endif

/* PXP */
#define ROTATE_DISPLAY kPXP_Rotate180
#define APP_PXP PXP

#define APP_LCD_BUFFER_COUNT 2

#define APP_IMG_WIDTH DEMO_PANEL_WIDTH
#define APP_IMG_HEIGHT DEMO_PANEL_HEIGHT

/* PS input buffer is square. */
#if APP_IMG_WIDTH > APP_IMG_HEIGHT
#define APP_PS_SIZE APP_IMG_WIDTH
#else
#define APP_PS_SIZE APP_IMG_HEIGHT
#endif

#define APP_PS_ULC_X 0U
#define APP_PS_ULC_Y 0U
#define APP_PS_LRC_X (APP_IMG_WIDTH -1U)
#define APP_PS_LRC_Y (APP_IMG_HEIGHT- 1U)

#define APP_RED 0xF100U
#define APP_GREEN 0x07E0U
#define APP_BLUE 0x001FU
#define APP_WHITE 0xFFFFU
#define APP_PXP_PS_FORMAT kPXP_PsPixelFormatRGB565
#define APP_PXP_AS_FORMAT kPXP_AsPixelFormatRGB565
#define APP_PXP_OUT_FORMAT kPXP_OutputPixelFormatRGB565
#define APP_DC_FORMAT kVIDEO_PixelFormatRGB565

/* Tresholds */
#define DETECTION_TRESHOLD 60

#define INPUT_MEAN_SHIFT {125,123,114}
#define INPUT_RIGHT_SHIFT {8,8,8}



/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void APP_BufferSwitchOffCallback(void *param, void *switchOffBuffer);
static void APP_CSIFullBufferReady(camera_receiver_handle_t *handle,
                                  status_t status, void *userData);
static void APP_Rotate(uint32_t input_buffer, uint32_t output_buffer);
static void APP_InitPxp(void);
static void APP_InitCamera(void);
static void APP_InitDisplay(void);
static void APP_CsiRgb565Start(void);
static void APP_CsiRgb565Refresh(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/
#if !defined(__ARMCC_VERSION)
AT_NONCACHEABLE_SECTION_ALIGN(
    static uint16_t s_frameBuffer[APP_FRAME_BUFFER_COUNT][DEMO_PANEL_HEIGHT][DEMO_PANEL_WIDTH],
    CAMERA_FRAME_BUFFER_ALIGN);

AT_NONCACHEABLE_SECTION_ALIGN(
    static uint16_t s_lcdBuf[APP_LCD_BUFFER_COUNT][DEMO_PANEL_HEIGHT][DEMO_PANEL_WIDTH],
    CAMERA_FRAME_BUFFER_ALIGN);

#else
AT_NONCACHEABLE_SECTION_ALIGN_INIT(
    static uint16_t s_frameBuffer[APP_FRAME_BUFFER_COUNT][DEMO_PANEL_HEIGHT][DEMO_PANEL_WIDTH],
    CAMERA_FRAME_BUFFER_ALIGN);

AT_NONCACHEABLE_SECTION_ALIGN_INIT(
    static uint16_t s_lcdBuf[APP_LCD_BUFFER_COUNT][DEMO_PANEL_HEIGHT][DEMO_PANEL_WIDTH],
    CAMERA_FRAME_BUFFER_ALIGN);
#endif

/*
 * When new frame buffer sent to display, it might not be shown immediately.
 * Application could use callback to get new frame shown notification, at the
 * same time, when this flag is set, application could write to the older
 * frame buffer.
 */
static volatile bool s_newFrameShown = false;
static dc_fb_info_t fbInfo;

static volatile bool g_isCamDataExtracted = false;
static uint16_t pExtract[EXTRACT_WIDTH * EXTRACT_HEIGHT];

static uint32_t cameraReceivedFrameAddr;
static uint8_t curLcdBufferIdx = 0;

uint32_t max_idx, display_idx, last_max_idx;
float last_max_val=0;

static uint8_t s_data[EXTRACT_WIDTH * EXTRACT_HEIGHT * 3];

/*******************************************************************************
 * Code
 ******************************************************************************/
void GUI_DrawPixel(int color, int x, int y)
{
	unsigned int r=(color & 0xFF0000) >> 16;
	unsigned int g=(color & 0x00FF00) >> 8;
	unsigned int b=(color & 0x0000FF);
	DrawPixel((uint16_t*)s_lcdBuf[curLcdBufferIdx], x, y,  r,g, b);
}

/*!
 * @brief Rotate image PXP.
 * param input_buffer pointer to source image buffer.
 * param output_buffer pointer to output buffer for storing result.
 */
static void APP_Rotate(uint32_t input_buffer, uint32_t output_buffer)
{
  APP_PXP->PS_BUF = input_buffer;
  APP_PXP->OUT_BUF = output_buffer;
  /* Prepare next buffer for LCD. */
  PXP_SetRotateConfig(APP_PXP, kPXP_RotateOutputBuffer, ROTATE_DISPLAY, kPXP_FlipDisable);

  PXP_Start(APP_PXP);

  /* Wait for process complete. */
  while (!(kPXP_CompleteFlag & PXP_GetStatusFlags(APP_PXP)))
  {
  }

  PXP_ClearStatusFlags(APP_PXP, kPXP_CompleteFlag);
}

/*!
 * @brief Initializes PXP.
 */
static void APP_InitPxp(void)
{
  PXP_Init(APP_PXP);

  /* PS configure. */
  const pxp_ps_buffer_config_t psBufferConfig = {
    .pixelFormat = APP_PXP_PS_FORMAT,
    .swapByte    = false,
    .bufferAddr  = 0U,
    .bufferAddrU = 0U,
    .bufferAddrV = 0U,
    .pitchBytes  = APP_PS_SIZE * APP_BPP,
  };

  PXP_SetProcessSurfaceBackGroundColor(APP_PXP, 0U);

  PXP_SetProcessSurfaceBufferConfig(APP_PXP, &psBufferConfig);
  PXP_SetProcessSurfacePosition(APP_PXP, APP_PS_ULC_X, APP_PS_ULC_Y, APP_PS_LRC_X, APP_PS_LRC_Y);

  /* Disable AS. */
  PXP_SetAlphaSurfacePosition(APP_PXP, 0xFFFFU, 0xFFFFU, 0U, 0U);

  pxp_output_buffer_config_t outputBufferConfig;
  /* Output config. */
  outputBufferConfig.pixelFormat    = APP_PXP_OUT_FORMAT;
  outputBufferConfig.interlacedMode = kPXP_OutputProgressive;
  outputBufferConfig.buffer0Addr    = 0U;
  outputBufferConfig.buffer1Addr    = 0U;
  outputBufferConfig.pitchBytes     = APP_IMG_WIDTH * APP_BPP;
  outputBufferConfig.width          = APP_IMG_WIDTH;
  outputBufferConfig.height         = APP_IMG_HEIGHT;

  PXP_SetOutputBufferConfig(APP_PXP, &outputBufferConfig);

  /* Disable CSC1, it is enabled by default. */
  PXP_EnableCsc1(APP_PXP, false);
}

/*!
 * @brief Initializes camera.
 */
static void APP_InitCamera(void)
{
  const camera_config_t cameraConfig = {
    .pixelFormat   = kVIDEO_PixelFormatRGB565,
    .bytesPerPixel = APP_BPP,
    .resolution    = FSL_VIDEO_RESOLUTION(DEMO_CAMERA_WIDTH, DEMO_CAMERA_HEIGHT),
    /* Set the camera buffer stride according to panel, so that if
     * camera resoution is smaller than display, it can still be shown
     * correct in the screen.
     */
    .frameBufferLinePitch_Bytes = DEMO_PANEL_WIDTH * APP_BPP,
    .interface                  = kCAMERA_InterfaceGatedClock,
    .controlFlags               = DEMO_CAMERA_CONTROL_FLAGS,
    .framePerSec                = 30,
  };
  
  memset(s_frameBuffer, 0, sizeof(s_frameBuffer));

  BOARD_InitCameraResource();
  CAMERA_RECEIVER_Init(&cameraReceiver, &cameraConfig, APP_CSIFullBufferReady, NULL);
  if (kStatus_Success != CAMERA_DEVICE_Init(&cameraDevice, &cameraConfig))
  {
    PRINTF("Camera device initialization failed\r\n");
    while (1) {}
  }
  CAMERA_DEVICE_Start(&cameraDevice);

  /* Submit the empty frame buffers to buffer queue. */
  for (uint32_t i = 0; i < APP_FRAME_BUFFER_COUNT; i++)
  {
     CAMERA_RECEIVER_SubmitEmptyBuffer(&cameraReceiver, (uint32_t)(s_frameBuffer[i]));
  }
}

/*!
 * @brief Initializes LCD.
 */
static void APP_InitDisplay(void)
{
  status_t status;

  BOARD_PrepareDisplayController();

  status = g_dc.ops->init(&g_dc);
  if (kStatus_Success != status)
  {
    PRINTF("Display initialization failed\r\n");
    assert(0);
  }

  g_dc.ops->getLayerDefaultConfig(&g_dc, 0, &fbInfo);
  fbInfo.pixelFormat = kVIDEO_PixelFormatRGB565;
  fbInfo.width       = DEMO_PANEL_WIDTH;
  fbInfo.height      = DEMO_PANEL_HEIGHT;
  fbInfo.strideBytes = DEMO_PANEL_WIDTH * APP_BPP;
  g_dc.ops->setLayerConfig(&g_dc, 0, &fbInfo);

  g_dc.ops->setCallback(&g_dc, 0, APP_BufferSwitchOffCallback, NULL);
}

/*!
 * @brief Start CSI processing.
 */
static void APP_CsiRgb565Start(void)
{
  CAMERA_RECEIVER_Start(&cameraReceiver);

  /* Wait to get the full frame buffer to show. */
  while (kStatus_Success !=
    CAMERA_RECEIVER_GetFullBuffer(&cameraReceiver, &cameraReceivedFrameAddr)) {}

  APP_Rotate(cameraReceivedFrameAddr, (uint32_t)s_lcdBuf[curLcdBufferIdx]);

  s_newFrameShown = false;
  g_dc.ops->setFrameBuffer(&g_dc, 0, (void *)s_lcdBuf[curLcdBufferIdx]);

  /* For the DBI interface display, application must wait for the first
     frame buffer sent to the panel. */
  if ((g_dc.ops->getProperty(&g_dc) & kDC_FB_ReserveFrameBuffer) == 0)
  {
    while (s_newFrameShown == false) {}
  }

  s_newFrameShown = true;

  g_dc.ops->enableLayer(&g_dc, 0);
}

/*!
 * @brief Process camera buffer and send it to LCD.
  */
static void APP_CsiRgb565Refresh()
{
  /* Wait to get the full frame buffer to show. */
  while (kStatus_Success !=
    CAMERA_RECEIVER_GetFullBuffer(&cameraReceiver, &cameraReceivedFrameAddr)) {}

  curLcdBufferIdx ^= 1U;
  APP_Rotate(cameraReceivedFrameAddr, (uint32_t)s_lcdBuf[curLcdBufferIdx]);

  /* Check if camera buffer is extracted for new inference. */
  if (!g_isCamDataExtracted)
  {
    /* Extract image from camera. */
    ExtractImage(pExtract, Rec_x, Rec_y, EXTRACT_WIDTH, EXTRACT_HEIGHT, (uint16_t *)cameraReceivedFrameAddr);

    /* Draw red rectangle when do extraction. */
    DrawRect((uint16_t*)s_lcdBuf[curLcdBufferIdx],Rec_x, Rec_y, EXTRACT_WIDTH, EXTRACT_HEIGHT, 255, 0, 0);
    g_isCamDataExtracted= true;
  }
  else
  {
    /* Draw white rectangle for aiming. */
    DrawRect((uint16_t*)s_lcdBuf[curLcdBufferIdx], Rec_x, Rec_y, EXTRACT_WIDTH, EXTRACT_HEIGHT, 255, 255, 255);
  }

  /* Print result to screen */
  GUI_printf(Rec_x+EXTRACT_WIDTH-8, Rec_y+EXTRACT_HEIGHT+20, LABELS[display_idx]);
  
  s_newFrameShown = false;
  g_dc.ops->setFrameBuffer(&g_dc, 0, (void *)s_lcdBuf[curLcdBufferIdx]);
}

/*!
 * @brief Set new empty buffer for CSI.
 */
static void APP_BufferSwitchOffCallback(void *param, void *switchOffBuffer)
{
  s_newFrameShown = true;
  CAMERA_RECEIVER_SubmitEmptyBuffer(&cameraReceiver, (uint32_t)cameraReceivedFrameAddr);
}

static void APP_CSIFullBufferReady(camera_receiver_handle_t *handle,
                                   status_t status, void *userData)
{
  if (s_newFrameShown)
  {
    APP_CsiRgb565Refresh();
  }
}


volatile int inference_result = -1;

volatile int count = 0;
/*!
 * @brief  Run inference. It processed static image if static image is not NULL
 * otherwise camera input is processed.
 *
 * param staticImage pointer to address of static image. Use NULL when static image
 * is not required.
 * param staticImageLen size of static image.
 */
void run_inference(const uint8_t *image_data, const char* labels[])
{
	  int8_t *bundleInput =(int8_t *)inputAddr;
	  //Do scaling on image.
	  for (int idx = 0; idx < MODEL_INPUT_SIZE; idx++)
	  {
	    int32_t tmp = image_data[idx];
	    tmp -= 128;
		bundleInput[idx]=((int8_t)(tmp));
	  }

	  mobilenet_quant(constantWeight, mutableWeight, activations);

	  // Get classification top1 result and confidence.
	  int8_t *out_data = (int8_t*)(outputAddr);
	  int8_t max_val = 0.0;
	  for(int i = 0; i < MODEL_NUM_OUTPUT_CLASSES; i++) {
		 //PRINTF("Confidence = 0.%03u\r\n",(int)(out_data[i]*1000));
	    if (out_data[i] > max_val) {
	      max_val = out_data[i];
	      max_idx = i;
	    }
	  }

	  //Update LCD display category if get same result twice in a row.
	  if(max_idx==last_max_idx)
	  {
		  display_idx=max_idx;
		  inference_result = max_idx;
	  }
	  last_max_idx=max_idx;

	  // Print classification results if Confidence > Threshold.
	  PRINTF("Top1 class = %lu (%s)\r\n", max_idx, LABELS[max_idx]);
	  PRINTF("Confidence = %lu \r\n",(int)(max_val));
	  //PRINTF("Inference time = %lu (ms)\r\n", duration_ms);
	  PRINTF("count from inference func: %d\r\n", count);
	  if(count == 1)
	  {
		  add_item(max_idx);
		  count = 0;
		  PRINTF("request sent to server\r\n");
	  }
}



/* Meichu Team 4 */

/* inference and send packet vars */
TimerHandle_t button_timer;
void sendPacket()
{
	xTimerStop(button_timer, 0);
	if (count == 1)
	{
		PRINTF("send add %d\r\n", inference_result);
		add_item(inference_result);
	}
	else
	{
		PRINTF("send remove %d\r\n", inference_result);
		remove_item(inference_result);
	}
	count = 0;
	xTimerReset(button_timer, 0);
}

void timer_callback(TimerHandle_t xTimer)
{
	// triggered every 500 ms
	PRINTF("timer callback\r\n");
	if (count == 0) return;
	else sendPacket();
}

void BOARD_USER_BUTTON_IRQ_HANDLER(void)
{
	count = 1;
	PRINTF("button irq count: %d\r\n", count);
	GPIO_PortClearInterruptFlags(BOARD_USER_BUTTON_GPIO, 1U << BOARD_USER_BUTTON_GPIO_PIN);
	SDK_ISR_EXIT_BARRIER;
}

void main_task(void * arg)
{

   gpio_pin_config_t sw_config = {
	  kGPIO_DigitalInput,
	  0,
	  kGPIO_IntRisingEdge,
  };

  EnableIRQ(BOARD_USER_BUTTON_IRQ);
  GPIO_PinInit(BOARD_USER_BUTTON_GPIO, BOARD_USER_BUTTON_GPIO_PIN, &sw_config);
  GPIO_PortEnableInterrupts(BOARD_USER_BUTTON_GPIO, 1U << BOARD_USER_BUTTON_GPIO_PIN);

  APP_InitCamera();
  APP_InitDisplay();
  APP_InitPxp();
  /* Start CSI transfer */
  APP_CsiRgb565Start();

  vTaskSuspend(NULL);
  /* wifi task done */
  vTaskSuspend(wifi_task_handler);

  //button_timer = xTimerCreate("button_timer", pdMS_TO_TICKS(500), pdTRUE, NULL, timer_callback);
  //xTimerStart(button_timer, 0);

  Image prev_scale = {
	.width = EXTRACT_WIDTH,
	.height = EXTRACT_HEIGHT,
	.channels = IMAGE_CHANNELS,
  };

  Image *after_scale;

  uint8_t wanted_width = MODEL_INPUT_WIDTH;
  uint8_t wanted_height = MODEL_INPUT_HEIGHT;
  double dx = 1.0 * wanted_width / EXTRACT_WIDTH;
  double dy = 1.0 * wanted_height / EXTRACT_HEIGHT;

  after_scale = ImCreate(&prev_scale, dx, dy);

  PRINTF("\r\nProcessing camera data\r\n");
  while (1)
  {
	if (g_isCamDataExtracted)
	{
		//Get extracted camera data and put it the proper order for this model
	   CSI2Image(s_data, EXTRACT_WIDTH, EXTRACT_HEIGHT, pExtract, MODEL_COLOR_ORDER, MODEL_IMAGE_LAYOUT);

	   /* Resize data array to MODEL_INPUT_WIDTH x MODEL_INPUT_HEIGHT*/
	   prev_scale.imageData = s_data;
	   after_scale = ImScale(&prev_scale, after_scale, dx, dy);

	   /* Convert the color image to monochrome */

	   /* Run inference on the resized and decolorized data */
	   run_inference(after_scale->imageData, LABELS);
	   g_isCamDataExtracted = false;
	}
  }
}

static int __scan_cb(unsigned int count)
{
    struct wlan_scan_result res;
    int i;
    int err;

    if (count == 0)
    {
        PRINTF("No networks found!\r\n");
        return 0;
    }

    PRINTF("%d network%s found:\r\n", count, count == 1 ? "" : "s");

    for (i = 0; i < count; i++)
    {
        err = wlan_get_scan_result(i, &res);
        if (err)
        {
            PRINTF("Error: can't get scan res %d\r\n", i);
            continue;
        }

        print_mac(res.bssid);

        if (res.ssid[0])
            PRINTF(" \"%s\"\r\n", res.ssid);
        else
            PRINTF(" (hidden) \r\n");

        PRINTF("\tchannel: %d\r\n", res.channel);
        PRINTF("\trssi: -%d dBm\r\n", res.rssi);
        PRINTF("\tsecurity: ");
        if (res.wep)
            PRINTF("WEP ");
        if (res.wpa && res.wpa2)
            PRINTF("WPA/WPA2 Mixed ");
        else
        {
            if (res.wpa)
                PRINTF("WPA ");
            if (res.wpa2)
                PRINTF("WPA2 ");
            if (res.wpa3_sae)
                PRINTF("WPA3 SAE ");
            if (res.wpa2_entp)
                PRINTF("WPA2 Enterprise");
        }
        if (!(res.wep || res.wpa || res.wpa2 || res.wpa3_sae || res.wpa2_entp))
            PRINTF("OPEN ");
        PRINTF("\r\n");

        PRINTF("\tWMM: %s\r\n", res.wmm ? "YES" : "NO");
    }

    firstResult = 1;
    return 0;
}
static void scan(void)
{
    if (wlan_scan(__scan_cb))
    {
        PRINTF("Error: scan request failed\r\n");
        __BKPT(0);
    }
    else
    {
        PRINTF("Scan scheduled...\r\n");
    }
}
static void conToAp(void)
{
    int ret;

    PRINTF("Connecting to %s .....", sta_network.ssid);

    ret = wlan_connect(sta_network.name);

    if (ret != WM_SUCCESS)
    {
        PRINTF("Failed to connect %d\r\n", ret);
    }
}

#define MAX_RETRY_TICKS 50

static int network_added = 0;

/* Callback Function passed to WLAN Connection Manager. The callback function
 * gets called when there are WLAN Events that need to be handled by the
 * application.
 */
int wlan_event_callback(enum wlan_event_reason reason, void *data)
{
    PRINTF("app_cb: WLAN: received event %d\r\n", reason);

    switch (reason)
    {
        case WLAN_REASON_INITIALIZED:
            PRINTF("app_cb: WLAN initialized\r\n");
            int ret;

            /* Print WLAN FW Version */
            wlan_version_extended();

            if (!network_added)
            {
                uint8_t network_name_len = 0;
                uint8_t ssid_len         = 0;
                uint8_t psk_len          = 0;
                memset(&sta_network, 0, sizeof(struct wlan_network));

                network_name_len = (strlen("sta_network") < WLAN_NETWORK_NAME_MAX_LENGTH) ?
                                       (strlen("sta_network") + 1) :
                                       WLAN_NETWORK_NAME_MAX_LENGTH;
                strncpy(sta_network.name, "sta_network", network_name_len);

                ssid_len = (strlen(AP_SSID) <= IEEEtypes_SSID_SIZE) ? strlen(AP_SSID) : IEEEtypes_SSID_SIZE;
                memcpy(sta_network.ssid, (const char *)AP_SSID, ssid_len);
                sta_network.ip.ipv4.addr_type = ADDR_TYPE_DHCP;
                sta_network.ssid_specific     = 1;

                if (strlen(AP_PASSPHRASE))
                {
                    sta_network.security.type = WLAN_SECURITY_WILDCARD;
                    psk_len = (strlen(AP_PASSPHRASE) <= (WLAN_PSK_MAX_LENGTH - 1)) ? strlen(AP_PASSPHRASE) :
                                                                                     (WLAN_PSK_MAX_LENGTH - 1);
                    strncpy(sta_network.security.psk, AP_PASSPHRASE, psk_len);
                    sta_network.security.psk_len = psk_len;
                }
                else
                {
                    sta_network.security.type = WLAN_SECURITY_NONE;
                }

                ret = wlan_add_network(&sta_network);

                if (ret != 0)
                {
                    PRINTF(" Failed to add network %d\r\n", ret);
                    return 0;
                }
                network_added = 1;
            }

            if (xInitTaskNotify != NULL)
            {
                xTaskNotify(xInitTaskNotify, WM_SUCCESS, eSetValueWithOverwrite);
                xInitTaskNotify = NULL;
            }

            break;
        case WLAN_REASON_INITIALIZATION_FAILED:
            PRINTF("app_cb: WLAN: initialization failed\r\n");

            if (xInitTaskNotify != NULL)
            {
                xTaskNotify(xInitTaskNotify, WM_FAIL, eSetValueWithOverwrite);
                xInitTaskNotify = NULL;
            }

            break;
        case WLAN_REASON_ADDRESS_SUCCESS:
            PRINTF("network mgr: DHCP new lease\r\n");
            break;
        case WLAN_REASON_ADDRESS_FAILED:
            PRINTF("app_cb: failed to obtain an IP address\r\n");
            break;
        case WLAN_REASON_USER_DISCONNECT:
            PRINTF("app_cb: disconnected\r\n");
            break;
        case WLAN_REASON_LINK_LOST:
            PRINTF("app_cb: WLAN: link lost\r\n");
            break;
        case WLAN_REASON_SUCCESS:
            PRINTF("Connected to [%s]\r\n", sta_network.ssid);
            if (xJoinTaskNotify != NULL)
            {
                xTaskNotify(xJoinTaskNotify, WM_SUCCESS, eSetValueWithOverwrite);
                xJoinTaskNotify = NULL;
            }
            break;
        case WLAN_REASON_CONNECT_FAILED:
            PRINTF("[!] WLAN: connect failed\r\n");
            if (xJoinTaskNotify != NULL)
            {
                xTaskNotify(xJoinTaskNotify, WM_FAIL, eSetValueWithOverwrite);
                xJoinTaskNotify = NULL;
            }
            break;
        case WLAN_REASON_NETWORK_NOT_FOUND:
            PRINTF("[!] WLAN: network not found\r\n");
            if (xJoinTaskNotify != NULL)
            {
                xTaskNotify(xJoinTaskNotify, WM_FAIL, eSetValueWithOverwrite);
                xJoinTaskNotify = NULL;
            }
            break;
        case WLAN_REASON_NETWORK_AUTH_FAILED:
            PRINTF("[!] Network Auth failed\r\n");
            if (xJoinTaskNotify != NULL)
            {
                xTaskNotify(xJoinTaskNotify, WM_FAIL, eSetValueWithOverwrite);
                xJoinTaskNotify = NULL;
            }
            break;
        default:
            PRINTF("app_cb: WLAN: Unknown Event: %d\r\n", reason);
    }
    return 0;
}
void wifi_task(void *param)
{
    int32_t result = 0;
    (void)result;
    ip4_addr_t ip;

    if (!ipaddr_aton(PING_ADDR, &ip))
    {
        PRINTF("Failed to convert %s to ip\r\n", PING_ADDR);
        __BKPT(0);
    }

    PRINTF("Initialize WLAN Driver\r\n");
    result = wlan_init(wlan_fw_bin, wlan_fw_bin_len);

    if (WM_SUCCESS != result)
    {
        PRINTF("Wlan initialization failed");
        __BKPT(0);
    }

    xInitTaskNotify = xTaskGetCurrentTaskHandle();
    result          = wlan_start(wlan_event_callback);
    if (WM_SUCCESS != result)
    {
        PRINTF("Couldn't start wlan\r\n");
        __BKPT(0);
    }

    // we need to wait for wi-fi initialization
    if (WM_SUCCESS == ulTaskNotifyTake(pdTRUE, portMAX_DELAY))
    {
        scan();
    }
    else
    {
        // WLAN: initialization failed
        __BKPT(0);
    }

    while (!firstResult)
    {
        os_thread_sleep(os_msec_to_ticks(500));
    }

    // Note down the Join task so that
    xJoinTaskNotify = xTaskGetCurrentTaskHandle();
    conToAp();
    if (WM_SUCCESS == ulTaskNotifyTake(pdTRUE, portMAX_DELAY))
    {
        PRINTF("Connection Successful\r\n");
    }
    else
    {
        PRINTF("Connection Failed! Stopping!\r\n");
        __BKPT(0);
    }

    vTaskResume(main_task_handler);

    for (;;)
        ;
}

/*!
 * @brief Main function
 */
int main(void)
{
  /* Init board hardware. */
  BOARD_ConfigMPU();
  BOARD_InitPins();
  BOARD_InitDEBUG_UARTPins();
  BOARD_InitSDRAMPins();
  BOARD_EarlyPrepareCamera();
  BOARD_InitCSIPins();
  BOARD_InitLCDPins();
  BOARD_BootClockRUN();
  BOARD_InitDebugConsole();

  NVIC_SetPriorityGrouping(3);
  //init_timer();

  PRINTF("Meichu Team 4 Professor Smart\r\n");

  BaseType_t result = xTaskCreate(wifi_task, "main", wifi_STACK_SIZE, wifi_stack, 2, &wifi_task_handler);
  //assert(pdPASS == result);

  /* Create the main Task (inference) */

  if (xTaskCreate(main_task, "main_task", 2048, NULL, 3, &main_task_handler) != pdPASS)
  {
	  PRINTF("[!] MAIN Task creation failed!\r\n");
	  while (1)
		  ;
  }

  /* Run RTOS */
  vTaskStartScheduler();

}


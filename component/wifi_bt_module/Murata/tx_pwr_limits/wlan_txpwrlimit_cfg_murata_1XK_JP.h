/** @file wlan_txpwrlimit_cfg_murata_1XK_JP.h
 *
 *  @brief  This file provides Murata 1XK WLAN JP Tx Power Limit APIs.
 *
 *  Copyright 2008-2020 NXP
 *
 *  NXP CONFIDENTIAL
 *  The source code contained or described herein and all documents related to
 *  the source code ("Materials") are owned by NXP, its
 *  suppliers and/or its licensors. Title to the Materials remains with NXP,
 *  its suppliers and/or its licensors. The Materials contain
 *  trade secrets and proprietary and confidential information of NXP, its
 *  suppliers and/or its licensors. The Materials are protected by worldwide copyright
 *  and trade secret laws and treaty provisions. No part of the Materials may be
 *  used, copied, reproduced, modified, published, uploaded, posted,
 *  transmitted, distributed, or disclosed in any way without NXP's prior
 *  express written permission.
 *
 *  No license under any patent, copyright, trade secret or other intellectual
 *  property right is granted to or conferred upon you by disclosure or delivery
 *  of the Materials, either expressly, by implication, inducement, estoppel or
 *  otherwise. Any license under such intellectual property rights must be
 *  express and approved by NXP in writing.
 *
 */

static wlan_chanlist_t chanlist_2g_cfg = {.num_chans = 13,
                                          .chan_info = {
                                              [0] =
                                                  {
                                                      .chan_num                     = 1,
                                                      .chan_freq                    = 2412,
                                                      .passive_scan_or_radar_detect = false,
                                                  },
                                              [1] =
                                                  {
                                                      .chan_num                     = 2,
                                                      .chan_freq                    = 2417,
                                                      .passive_scan_or_radar_detect = false,
                                                  },
                                              [2] =
                                                  {
                                                      .chan_num                     = 3,
                                                      .chan_freq                    = 2422,
                                                      .passive_scan_or_radar_detect = false,
                                                  },
                                              [3] =
                                                  {
                                                      .chan_num                     = 4,
                                                      .chan_freq                    = 2427,
                                                      .passive_scan_or_radar_detect = false,
                                                  },
                                              [4] =
                                                  {
                                                      .chan_num                     = 5,
                                                      .chan_freq                    = 2432,
                                                      .passive_scan_or_radar_detect = false,
                                                  },
                                              [5] =
                                                  {
                                                      .chan_num                     = 6,
                                                      .chan_freq                    = 2437,
                                                      .passive_scan_or_radar_detect = false,
                                                  },
                                              [6] =
                                                  {
                                                      .chan_num                     = 7,
                                                      .chan_freq                    = 2442,
                                                      .passive_scan_or_radar_detect = false,
                                                  },
                                              [7] =
                                                  {
                                                      .chan_num                     = 8,
                                                      .chan_freq                    = 2447,
                                                      .passive_scan_or_radar_detect = false,
                                                  },
                                              [8] =
                                                  {
                                                      .chan_num                     = 9,
                                                      .chan_freq                    = 2452,
                                                      .passive_scan_or_radar_detect = false,
                                                  },
                                              [9] =
                                                  {
                                                      .chan_num                     = 10,
                                                      .chan_freq                    = 2457,
                                                      .passive_scan_or_radar_detect = false,
                                                  },
                                              [10] =
                                                  {
                                                      .chan_num                     = 11,
                                                      .chan_freq                    = 2462,
                                                      .passive_scan_or_radar_detect = false,
                                                  },
                                              [11] =
                                                  {
                                                      .chan_num                     = 12,
                                                      .chan_freq                    = 2467,
                                                      .passive_scan_or_radar_detect = false,
                                                  },
                                              [12] =
                                                  {
                                                      .chan_num                     = 13,
                                                      .chan_freq                    = 2472,
                                                      .passive_scan_or_radar_detect = false,
                                                  },
                                              [13] = {0},
                                              [14] = {0},
                                              [15] = {0},
                                              [16] = {0},
                                              [17] = {0},
                                              [18] = {0},
                                              [19] = {0},
                                              [20] = {0},
                                              [21] = {0},
                                              [22] = {0},
                                              [23] = {0},
                                              [24] = {0},
                                              [25] = {0},
                                              [26] = {0},
                                              [27] = {0},
                                              [28] = {0},
                                              [29] = {0},
                                              [30] = {0},
                                              [31] = {0},
                                              [32] = {0},
                                              [33] = {0},
                                              [34] = {0},
                                              [35] = {0},
                                              [36] = {0},
                                              [37] = {0},
                                              [38] = {0},
                                              [39] = {0},
                                              [40] = {0},
                                              [41] = {0},
                                              [42] = {0},
                                              [43] = {0},
                                              [44] = {0},
                                              [45] = {0},
                                              [46] = {0},
                                              [47] = {0},
                                              [48] = {0},
                                              [49] = {0},
                                              [50] = {0},
                                              [51] = {0},
                                              [52] = {0},
                                              [53] = {0},
                                          }};

#ifdef CONFIG_5GHz_SUPPORT
static wlan_chanlist_t chanlist_5g_cfg = {.num_chans = 20,
                                          .chan_info = {
                                              [0] =
                                                  {
                                                      .chan_num                     = 36,
                                                      .chan_freq                    = 5180,
                                                      .passive_scan_or_radar_detect = false,
                                                  },
                                              [1] =
                                                  {
                                                      .chan_num                     = 40,
                                                      .chan_freq                    = 5200,
                                                      .passive_scan_or_radar_detect = false,
                                                  },
                                              [2] =
                                                  {
                                                      .chan_num                     = 44,
                                                      .chan_freq                    = 5220,
                                                      .passive_scan_or_radar_detect = false,
                                                  },
                                              [3] =
                                                  {
                                                      .chan_num                     = 48,
                                                      .chan_freq                    = 5240,
                                                      .passive_scan_or_radar_detect = false,
                                                  },
                                              [4] =
                                                  {
                                                      .chan_num                     = 52,
                                                      .chan_freq                    = 5260,
                                                      .passive_scan_or_radar_detect = true,
                                                  },
                                              [5] =
                                                  {
                                                      .chan_num                     = 56,
                                                      .chan_freq                    = 5280,
                                                      .passive_scan_or_radar_detect = true,
                                                  },
                                              [6] =
                                                  {
                                                      .chan_num                     = 60,
                                                      .chan_freq                    = 5300,
                                                      .passive_scan_or_radar_detect = true,
                                                  },
                                              [7] =
                                                  {
                                                      .chan_num                     = 64,
                                                      .chan_freq                    = 5320,
                                                      .passive_scan_or_radar_detect = true,
                                                  },
                                              [8] =
                                                  {
                                                      .chan_num                     = 100,
                                                      .chan_freq                    = 5500,
                                                      .passive_scan_or_radar_detect = true,
                                                  },
                                              [9] =
                                                  {
                                                      .chan_num                     = 104,
                                                      .chan_freq                    = 5520,
                                                      .passive_scan_or_radar_detect = true,
                                                  },
                                              [10] =
                                                  {
                                                      .chan_num                     = 108,
                                                      .chan_freq                    = 5540,
                                                      .passive_scan_or_radar_detect = true,
                                                  },
                                              [11] =
                                                  {
                                                      .chan_num                     = 112,
                                                      .chan_freq                    = 5560,
                                                      .passive_scan_or_radar_detect = true,
                                                  },
                                              [12] =
                                                  {
                                                      .chan_num                     = 116,
                                                      .chan_freq                    = 5580,
                                                      .passive_scan_or_radar_detect = true,
                                                  },
                                              [13] =
                                                  {
                                                      .chan_num                     = 120,
                                                      .chan_freq                    = 5600,
                                                      .passive_scan_or_radar_detect = true,
                                                  },
                                              [14] =
                                                  {
                                                      .chan_num                     = 124,
                                                      .chan_freq                    = 5620,
                                                      .passive_scan_or_radar_detect = true,
                                                  },
                                              [15] =
                                                  {
                                                      .chan_num                     = 128,
                                                      .chan_freq                    = 5640,
                                                      .passive_scan_or_radar_detect = true,
                                                  },
                                              [16] =
                                                  {
                                                      .chan_num                     = 132,
                                                      .chan_freq                    = 5660,
                                                      .passive_scan_or_radar_detect = true,
                                                  },
                                              [17] =
                                                  {
                                                      .chan_num                     = 136,
                                                      .chan_freq                    = 5680,
                                                      .passive_scan_or_radar_detect = true,
                                                  },
                                              [18] =
                                                  {
                                                      .chan_num                     = 140,
                                                      .chan_freq                    = 5700,
                                                      .passive_scan_or_radar_detect = true,
                                                  },
                                              [19] =
                                                  {
                                                      .chan_num                     = 144,
                                                      .chan_freq                    = 5720,
                                                      .passive_scan_or_radar_detect = true,
                                                  },
                                              [20] = {0},
                                              [21] = {0},
                                              [22] = {0},
                                              [23] = {0},
                                              [24] = {0},
                                              [25] = {0},
                                              [26] = {0},
                                              [27] = {0},
                                              [28] = {0},
                                              [29] = {0},
                                              [30] = {0},
                                              [31] = {0},
                                              [32] = {0},
                                              [33] = {0},
                                              [34] = {0},
                                              [35] = {0},
                                              [36] = {0},
                                              [37] = {0},
                                              [38] = {0},
                                              [39] = {0},
                                              [40] = {0},
                                              [41] = {0},
                                              [42] = {0},
                                              [43] = {0},
                                              [44] = {0},
                                              [45] = {0},
                                              [46] = {0},
                                              [47] = {0},
                                              [48] = {0},
                                              [49] = {0},
                                              [50] = {0},
                                              [51] = {0},
                                              [52] = {0},
                                              [53] = {0},
                                          }};
#endif

static wifi_txpwrlimit_t
    tx_pwrlimit_2g_cfg =
        {.subband   = (wifi_SubBand_t)0x00,
         .num_chans = 13,
         .txpwrlimit_config =
             {
                 [0] =
                     {
                         .num_mod_grps = 10,
                         .chan_desc =
                             {
                                 .start_freq = 2407,
                                 .chan_width = 20,
                                 .chan_num   = 1,
                             },
                         .txpwrlimit_entry =
                             {{0, 16}, {1, 17}, {2, 16}, {3, 16}, {4, 16}, {5, 15}, {6, 15}, {7, 0}, {8, 0}, {9, 0}},
                     },
                 [1] =
                     {
                         .num_mod_grps = 10,
                         .chan_desc =
                             {
                                 .start_freq = 2407,
                                 .chan_width = 20,
                                 .chan_num   = 2,
                             },
                         .txpwrlimit_entry =
                             {{0, 16}, {1, 17}, {2, 16}, {3, 16}, {4, 16}, {5, 15}, {6, 15}, {7, 0}, {8, 0}, {9, 0}},
                     },
                 [2] =
                     {
                         .num_mod_grps = 10,
                         .chan_desc =
                             {
                                 .start_freq = 2407,
                                 .chan_width = 20,
                                 .chan_num   = 3,
                             },
                         .txpwrlimit_entry =
                             {{0, 16}, {1, 17}, {2, 16}, {3, 16}, {4, 16}, {5, 15}, {6, 15}, {7, 0}, {8, 0}, {9, 0}},
                     },
                 [3] =
                     {
                         .num_mod_grps = 10,
                         .chan_desc =
                             {
                                 .start_freq = 2407,
                                 .chan_width = 20,
                                 .chan_num   = 4,
                             },
                         .txpwrlimit_entry =
                             {{0, 16}, {1, 17}, {2, 16}, {3, 16}, {4, 16}, {5, 15}, {6, 15}, {7, 0}, {8, 0}, {9, 0}},
                     },
                 [4] =
                     {
                         .num_mod_grps = 10,
                         .chan_desc =
                             {
                                 .start_freq = 2407,
                                 .chan_width = 20,
                                 .chan_num   = 5,
                             },
                         .txpwrlimit_entry =
                             {{0, 16}, {1, 17}, {2, 16}, {3, 16}, {4, 16}, {5, 15}, {6, 15}, {7, 0}, {8, 0}, {9, 0}},
                     },
                 [5] =
                     {
                         .num_mod_grps = 10,
                         .chan_desc =
                             {
                                 .start_freq = 2407,
                                 .chan_width = 20,
                                 .chan_num   = 6,
                             },
                         .txpwrlimit_entry =
                             {{0, 16}, {1, 17}, {2, 16}, {3, 16}, {4, 16}, {5, 15}, {6, 15}, {7, 0}, {8, 0}, {9, 0}},
                     },
                 [6] =
                     {
                         .num_mod_grps = 10,
                         .chan_desc =
                             {
                                 .start_freq = 2407,
                                 .chan_width = 20,
                                 .chan_num   = 7,
                             },
                         .txpwrlimit_entry =
                             {{0, 16}, {1, 17}, {2, 16}, {3, 16}, {4, 16}, {5, 15}, {6, 15}, {7, 0}, {8, 0}, {9, 0}},
                     },
                 [7] =
                     {
                         .num_mod_grps = 10,
                         .chan_desc =
                             {
                                 .start_freq = 2407,
                                 .chan_width = 20,
                                 .chan_num   = 8,
                             },
                         .txpwrlimit_entry =
                             {{0, 16}, {1, 17}, {2, 16}, {3, 16}, {4, 16}, {5, 15}, {6, 15}, {7, 0}, {8, 0}, {9, 0}},
                     },
                 [8] =
                     {
                         .num_mod_grps = 10,
                         .chan_desc =
                             {
                                 .start_freq = 2407,
                                 .chan_width = 20,
                                 .chan_num   = 9,
                             },
                         .txpwrlimit_entry =
                             {{0, 16}, {1, 17}, {2, 16}, {3, 16}, {4, 16}, {5, 15}, {6, 15}, {7, 0}, {8, 0}, {9, 0}},
                     },
                 [9] =
                     {
                         .num_mod_grps = 10,
                         .chan_desc =
                             {
                                 .start_freq = 2407,
                                 .chan_width = 20,
                                 .chan_num   = 10,
                             },
                         .txpwrlimit_entry =
                             {{0, 16}, {1, 17}, {2, 16}, {3, 16}, {4, 16}, {5, 15}, {6, 15}, {7, 0}, {8, 0}, {9, 0}},
                     },
                 [10] =
                     {
                         .num_mod_grps = 10,
                         .chan_desc =
                             {
                                 .start_freq = 2407,
                                 .chan_width = 20,
                                 .chan_num   = 11,
                             },
                         .txpwrlimit_entry =
                             {{0, 16}, {1, 17}, {2, 16}, {3, 16}, {4, 16}, {5, 15}, {6, 15}, {7, 0}, {8, 0}, {9, 0}},
                     },
                 [11] =
                     {
                         .num_mod_grps = 10,
                         .chan_desc =
                             {
                                 .start_freq = 2407,
                                 .chan_width = 20,
                                 .chan_num   = 12,
                             },
                         .txpwrlimit_entry =
                             {{0, 16}, {1, 17}, {2, 16}, {3, 16}, {4, 16}, {5, 15}, {6, 15}, {7, 0}, {8, 0}, {9, 0}},
                     },
                 [12] =
                     {
                         .num_mod_grps = 10,
                         .chan_desc =
                             {
                                 .start_freq = 2407,
                                 .chan_width = 20,
                                 .chan_num   = 13,
                             },
                         .txpwrlimit_entry =
                             {{0, 16}, {1, 17}, {2, 16}, {3, 16}, {4, 16}, {5, 15}, {6, 15}, {7, 0}, {8, 0}, {9, 0}},
                     },
                 [13] = {0},
                 [14] = {0},
                 [15] = {0},
                 [16] = {0},
                 [17] = {0},
                 [18] = {0},
                 [19] = {0},
                 [20] = {0},
                 [21] = {0},
                 [22] = {0},
                 [23] = {0},
                 [24] = {0},
                 [25] = {0},
                 [26] = {0},
                 [27] = {0},
                 [28] = {0},
                 [29] = {0},
                 [30] = {0},
                 [31] = {0},
                 [32] = {0},
                 [33] = {0},
                 [34] = {0},
                 [35] = {0},
                 [36] = {0},
                 [37] = {0},
                 [38] = {0},
                 [39] = {0},
             }};

#ifdef CONFIG_5GHz_SUPPORT
static wifi_txpwrlimit_t tx_pwrlimit_5g_cfg =
    {
        .subband   = (wifi_SubBand_t)0x00,
        .num_chans = 20,
        .txpwrlimit_config =
            {
                [0] =
                    {
                        .num_mod_grps = 9,
                        .chan_desc =
                            {
                                .start_freq = 5000,
                                .chan_width = 20,
                                .chan_num   = 36,
                            },
                        .txpwrlimit_entry =
                            {{1, 14}, {2, 14}, {3, 14}, {4, 14}, {5, 14}, {6, 14}, {7, 14}, {8, 14}, {9, 14}, {0, 0}},
                    },
                [1] =
                    {
                        .num_mod_grps = 9,
                        .chan_desc =
                            {
                                .start_freq = 5000,
                                .chan_width = 20,
                                .chan_num   = 40,
                            },
                        .txpwrlimit_entry =
                            {{1, 14}, {2, 14}, {3, 14}, {4, 14}, {5, 14}, {6, 14}, {7, 14}, {8, 14}, {9, 14}, {0, 0}},
                    },
                [2] =
                    {
                        .num_mod_grps = 9,
                        .chan_desc =
                            {
                                .start_freq = 5000,
                                .chan_width = 20,
                                .chan_num   = 44,
                            },
                        .txpwrlimit_entry =
                            {{1, 14}, {2, 14}, {3, 14}, {4, 14}, {5, 14}, {6, 14}, {7, 14}, {8, 14}, {9, 14}, {0, 0}},
                    },
                [3] =
                    {
                        .num_mod_grps = 9,
                        .chan_desc =
                            {
                                .start_freq = 5000,
                                .chan_width = 20,
                                .chan_num   = 48,
                            },
                        .txpwrlimit_entry =
                            {{1, 14}, {2, 14}, {3, 14}, {4, 14}, {5, 14}, {6, 14}, {7, 14}, {8, 14}, {9, 14}, {0, 0}},
                    },
                [4] =
                    {
                        .num_mod_grps = 9,
                        .chan_desc =
                            {
                                .start_freq = 5000,
                                .chan_width = 20,
                                .chan_num   = 52,
                            },
                        .txpwrlimit_entry =
                            {{1, 14}, {2, 14}, {3, 14}, {4, 14}, {5, 14}, {6, 14}, {7, 14}, {8, 14}, {9, 14}, {0, 0}},
                    },
                [5] =
                    {
                        .num_mod_grps = 9,
                        .chan_desc =
                            {
                                .start_freq = 5000,
                                .chan_width = 20,
                                .chan_num   = 56,
                            },
                        .txpwrlimit_entry =
                            {{1, 14}, {2, 14}, {3, 14}, {4, 14}, {5, 14}, {6, 14}, {7, 14}, {8, 14}, {9, 14}, {0, 0}},
                    },
                [6] =
                    {
                        .num_mod_grps = 9,
                        .chan_desc =
                            {
                                .start_freq = 5000,
                                .chan_width = 20,
                                .chan_num   = 60,
                            },
                        .txpwrlimit_entry =
                            {{1, 14}, {2, 14}, {3, 14}, {4, 14}, {5, 14}, {6, 14}, {7, 14}, {8, 14}, {9, 14}, {0, 0}},
                    },
                [7] =
                    {
                        .num_mod_grps = 9,
                        .chan_desc =
                            {
                                .start_freq = 5000,
                                .chan_width = 20,
                                .chan_num   = 64,
                            },
                        .txpwrlimit_entry =
                            {{1, 14}, {2, 14}, {3, 14}, {4, 14}, {5, 14}, {6, 14}, {7, 14}, {8, 14}, {9, 14}, {0, 0}},
                    },
                [8] =
                    {
                        .num_mod_grps = 9,
                        .chan_desc =
                            {
                                .start_freq = 5000,
                                .chan_width = 20,
                                .chan_num   = 100,
                            },
                        .txpwrlimit_entry =
                            {{1, 15}, {2, 15}, {3, 15}, {4, 14}, {5, 14}, {6, 14}, {7, 14}, {8, 14}, {9, 14}, {0, 0}},
                    },
                [9] =
                    {
                        .num_mod_grps = 9,
                        .chan_desc =
                            {
                                .start_freq = 5000,
                                .chan_width = 20,
                                .chan_num   = 104,
                            },
                        .txpwrlimit_entry =
                            {{1, 15}, {2, 15}, {3, 15}, {4, 14}, {5, 14}, {6, 14}, {7, 14}, {8, 14}, {9, 14}, {0, 0}},
                    },
                [10] =
                    {
                        .num_mod_grps = 9,
                        .chan_desc =
                            {
                                .start_freq = 5000,
                                .chan_width = 20,
                                .chan_num   = 108,
                            },
                        .txpwrlimit_entry =
                            {{1, 15}, {2, 15}, {3, 15}, {4, 14}, {5, 14}, {6, 14}, {7, 14}, {8, 14}, {9, 14}, {0, 0}},
                    },
                [11] =
                    {
                        .num_mod_grps = 9,
                        .chan_desc =
                            {
                                .start_freq = 5000,
                                .chan_width = 20,
                                .chan_num   = 112,
                            },
                        .txpwrlimit_entry =
                            {{1, 15}, {2, 15}, {3, 15}, {4, 14}, {5, 14}, {6, 14}, {7, 14}, {8, 14}, {9, 14}, {0, 0}},
                    },
                [12] =
                    {
                        .num_mod_grps = 9,
                        .chan_desc =
                            {
                                .start_freq = 5000,
                                .chan_width = 20,
                                .chan_num   = 116,
                            },
                        .txpwrlimit_entry =
                            {{1, 15}, {2, 15}, {3, 15}, {4, 14}, {5, 14}, {6, 14}, {7, 14}, {8, 14}, {9, 14}, {0, 0}},
                    },
                [13] =
                    {
                        .num_mod_grps = 9,
                        .chan_desc =
                            {
                                .start_freq = 5000,
                                .chan_width = 20,
                                .chan_num   = 120,
                            },
                        .txpwrlimit_entry =
                            {{1, 15}, {2, 15}, {3, 15}, {4, 14}, {5, 14}, {6, 14}, {7, 14}, {8, 14}, {9, 14}, {0, 0}},
                    },
                [14] =
                    {
                        .num_mod_grps = 9,
                        .chan_desc =
                            {
                                .start_freq = 5000,
                                .chan_width = 20,
                                .chan_num   = 124,
                            },
                        .txpwrlimit_entry =
                            {{1, 15}, {2, 15}, {3, 15}, {4, 14}, {5, 14}, {6, 14}, {7, 14}, {8, 14}, {9, 14}, {0, 0}},
                    },
                [15] =
                    {
                        .num_mod_grps = 9,
                        .chan_desc =
                            {
                                .start_freq = 5000,
                                .chan_width = 20,
                                .chan_num   = 128,
                            },
                        .txpwrlimit_entry =
                            {{1, 15}, {2, 15}, {3, 15}, {4, 14}, {5, 14}, {6, 14}, {7, 14}, {8, 14}, {9, 14}, {0, 0}},
                    },
                [16] =
                    {
                        .num_mod_grps = 9,
                        .chan_desc =
                            {
                                .start_freq = 5000,
                                .chan_width = 20,
                                .chan_num   = 132,
                            },
                        .txpwrlimit_entry =
                            {{1, 15}, {2, 15}, {3, 15}, {4, 14}, {5, 14}, {6, 14}, {7, 14}, {8, 14}, {9, 14}, {0, 0}},
                    },
                [17] =
                    {
                        .num_mod_grps = 9,
                        .chan_desc =
                            {
                                .start_freq = 5000,
                                .chan_width = 20,
                                .chan_num   = 136,
                            },
                        .txpwrlimit_entry =
                            {{1, 15}, {2, 15}, {3, 15}, {4, 14}, {5, 14}, {6, 14}, {7, 14}, {8, 14}, {9, 14}, {0, 0}},
                    },
                [18] =
                    {
                        .num_mod_grps = 9,
                        .chan_desc =
                            {
                                .start_freq = 5000,
                                .chan_width = 20,
                                .chan_num   = 140,
                            },
                        .txpwrlimit_entry =
                            {{1, 15}, {2, 15}, {3, 15}, {4, 14}, {5, 14}, {6, 14}, {7, 14}, {8, 14}, {9, 14}, {0, 0}},
                    },
                [19] =
                    {
                        .num_mod_grps = 9,
                        .chan_desc =
                            {
                                .start_freq = 5000,
                                .chan_width = 20,
                                .chan_num   = 144,
                            },
                        .txpwrlimit_entry =
                            {{1, 15}, {2, 15}, {3, 15}, {4, 14}, {5, 14}, {6, 14}, {7, 14}, {8, 14}, {9, 14}, {0, 0}},
                    },
                [20] = {0},
                [21] = {0},
                [22] = {0},
                [23] = {0},
                [24] = {0},
                [25] = {0},
                [26] = {0},
                [27] = {0},
                [28] = {0},
                [29] = {0},
                [30] = {0},
                [31] = {0},
                [32] = {0},
                [33] = {0},
                [34] = {0},
                [35] = {0},
                [36] = {0},
                [37] = {0},
                [38] = {0},
                [39] = {0},
            }};
#endif

/*
 * client.h
 *
 *  Created on: 2022年10月22日
 *      Author: brian1009
 */

#ifndef CLIENT_H_
#define CLIENT_H_

void add_item(int item_id);
void remove_item(int item_id);
void send_request(const char path[]);

#endif /* CLIENT_H_ */

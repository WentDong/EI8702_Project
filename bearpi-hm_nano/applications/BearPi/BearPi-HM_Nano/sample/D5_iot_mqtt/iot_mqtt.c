/*******************************************************************************
 * Copyright (c) 2014 IBM Corp.
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * and Eclipse Distribution License v1.0 which accompany this distribution.
 *
 * The Eclipse Public License is available at
 *    http://www.eclipse.org/legal/epl-v10.html
 * and the Eclipse Distribution License is available at
 *   http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * Contributors:
 *    Ian Craggs - initial API and implementation and/or initial documentation
 *    Sergio R. Caprile - clarifications and/or documentation extension
 *******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ohos_init.h"
#include "cmsis_os2.h"

#include "wifi_connect.h"
#include "MQTTClient.h"




static unsigned char sendBuf[1000];
static unsigned char readBuf[1000];

Network network;

void messageArrived(MessageData* data)
{
	printf("Message arrived on topic %.*s: %.*s\n", data->topicName->lenstring.len, data->topicName->lenstring.data,
		data->message->payloadlen, data->message->payload);
}

/* */

static void MQTT_DemoTask(void)
{
	WifiConnect("Hold","0987654321");
	printf("Starting ...\n");
	int rc, count = 0;
	MQTTClient client;

	NetworkInit(&network);
	printf("NetworkConnect  ...\n");
begin:	
	NetworkConnect(&network, "192.168.0.176", 1883);
	printf("MQTTClientInit  ...\n");
	MQTTClientInit(&client, &network, 2000, sendBuf, sizeof(sendBuf), readBuf, sizeof(readBuf));

	MQTTString clientId = MQTTString_initializer;
	clientId.cstring = "bearpi";

	MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
  	data.clientID          = clientId;
	data.willFlag          = 0;
	data.MQTTVersion       = 3;
	data.keepAliveInterval = 60;
	data.cleansession      = 1;

	printf("MQTTConnect  ...\n");
	rc = MQTTConnect(&client, &data);
	if (rc != 0) {
		printf("MQTTConnect: %d\n", rc);
		NetworkDisconnect(&network);
		MQTTDisconnect(&client);
		osDelay(200);
		goto begin;
	}

	printf("MQTTSubscribe  ...\n");
	rc = MQTTSubscribe(&client, "substopic", 2, messageArrived);
	if (rc != 0) {
		printf("MQTTSubscribe: %d\n", rc);
		osDelay(200);
		goto begin;
	}
	while (++count)
	{
		MQTTMessage message;
		char payload[30];

		message.qos = 2;
		message.retained = 0;
		message.payload = payload;
		sprintf(payload, "message number %d", count);
		message.payloadlen = strlen(payload);

		if ((rc = MQTTPublish(&client, "pubtopic", &message)) != 0){
			printf("Return code from MQTT publish is %d\n", rc);
			NetworkDisconnect(&network);
			MQTTDisconnect(&client);
			goto begin;
		}
		osDelay(50);	
	}
}
static void MQTT_Demo(void)
{
    osThreadAttr_t attr;

    attr.name = "MQTT_DemoTask";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = 10240;
    attr.priority = osPriorityNormal;

    if (osThreadNew((osThreadFunc_t)MQTT_DemoTask, NULL, &attr) == NULL) {
        printf("[MQTT_Demo] Falied to create MQTT_DemoTask!\n");
    }
}

APP_FEATURE_INIT(MQTT_Demo);
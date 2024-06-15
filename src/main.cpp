/*
 * Copyright (C) 2017 Obermaier Johannes
 * Copyright (C) 2022 Lucas Teske
 *
 * This Source Code Form is subject to the terms of the MIT License.
 * If a copy of the MIT License was not distributed with this file,
 * you can obtain one at https://opensource.org/licenses/MIT
 */

#include <Arduino.h>

extern "C" {
    #include "main.h"
    #include "reader.h"
}

// Usually the STM32F0x starts here.
// If you're trying to dump another series check the datasheet.
uint32_t flashStart = 0x08000000;
uint32_t flashEnd = 0x08010000;

void setup() {
    Serial.begin(115200);

    pinMode(TARGET_RESET_Pin, OUTPUT);
    pinMode(TARGET_PWR_Pin, OUTPUT);
    pinMode(SWDIO_Pin, OUTPUT);
    pinMode(SWCLK_Pin, OUTPUT);
}

void loop() {
    targetInit();
    digitalWrite(LED1_Pin, HIGH);
    while(!Serial.available()) {
        delay(1000);
        Serial.println("Send anything to start...");
    }
    Serial.readString();
    Serial.println("Starting");

    swdStatus_t status;
    uint32_t flashData = 0;
    uint32_t dummyRetries = 0;
    uint32_t addr = flashStart;
    while (addr < flashEnd) {
        if (Serial.available()) {
            Serial.readString();
            break;
        }
        flashData = 0;
        status = extractFlashData(addr, &flashData);
        if (status != swdStatusOk) {
            Serial.printf("Error reading: %d\r\n", status);
            break;
        }
        if (flashData == DUMMY_VALUE) {
            if (dummyRetries < DUMMY_READ_ATTEMPTS) {
                dummyRetries += 1;
                continue;
            }
        }
        Serial.printf("%08x: %08x\r\n", addr, flashData);
        dummyRetries = 0;
        addr += 4;
    }
    Serial.println("DONE");
}
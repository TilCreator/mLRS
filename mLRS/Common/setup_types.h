//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// Setup and configuration types
//*******************************************************
#ifndef SETUP_TYPES_H
#define SETUP_TYPES_H
#pragma once


#include <stdint.h>


//-------------------------------------------------------
// Setup Enums
//-------------------------------------------------------

//-- common to Tx & Rx

typedef enum {
    SETUP_FREQUENCY_BAND_2P4_GHZ = 0,
    SETUP_FREQUENCY_BAND_915_MHZ_FCC,
    SETUP_FREQUENCY_BAND_868_MHZ,
    SETUP_FREQUENCY_BAND_NUM,
} SETUP_FREQUENCY_BAND_ENUM;


typedef enum {
    MODE_50HZ = 0,
    MODE_31HZ,
    MODE_19HZ,
    MODE_NUM,
} MODE_ENUM;


typedef enum {
    DIVERSITY_DEFAULT = 0,
    DIVERSITY_ANTENNA1, // antenna 1 if diversity available
    DIVERSITY_ANTENNA2, // antenna 2 if diversity available
    DIVERSITY_NUM,
} DIVERSITY_ENUM;


typedef enum {
    SERIAL_BAUDRATE_9600 = 0,
    SERIAL_BAUDRATE_19200,
    SERIAL_BAUDRATE_38400,
    SERIAL_BAUDRATE_57600,
    SERIAL_BAUDRATE_115200,
    SERIAL_BAUDRATE_230400,
    SERIAL_BAUDRATE_NUM,
} SERIAL_BAUDRATE_ENUM;


typedef enum {
    CHANNEL_ORDER_AETR = 0, // most common
    CHANNEL_ORDER_TAER, // spektrum/graupner/jr
    CHANNEL_ORDER_ETAR,
    CHANNEL_ORDER_NUM,
} CHANNEL_ORDER_ENUM;


typedef enum {
    SERIAL_LINK_MODE_TRANSPARENT = 0,
    SERIAL_LINK_MODE_MAVLINK,
    SERIAL_LINK_MODE_NUM,
} SERIAL_LINK_MODE_ENUM;


typedef enum {
    SEND_RADIO_STATUS_OFF = 0,
    SEND_RADIO_STATUS_1HZ,
    SEND_RADIO_STATUS_2HZ,
    SEND_RADIO_STATUS_3HZ,
    SEND_RADIO_STATUS_4HZ,
    SEND_RADIO_STATUS_NUM,
} SEND_RADIO_STATUS_ENUM;


typedef enum {
    RADIO_STATUS_METHOD_DEFAULT = 0,
    RADIO_STATUS_METHOD_W_TXBUF,
    RADIO_STATUS_METHOD_PX4,
    RADIO_STATUS_METHOD_NUM,
} RADIO_STATUS_METHOD_ENUM;


//-- Tx only

typedef enum {
    SERIAL_DESTINATION_SERIAL = 0,
    SERIAL_DESTINATION_MBRDIGE,
    SERIAL_DESTINATION_SERIAL2,
    SERIAL_DESTINATION_NUM,
} TX_SERIAL_DESTINATION_ENUM;


typedef enum {
    CHANNEL_SOURCE_NONE = 0,
    CHANNEL_SOURCE_MBRIDGE, // JR pin5
    CHANNEL_SOURCE_INPORT, // In port
    CHANNEL_SOURCE_CRSF, // JR pin5
    CHANNEL_SOURCE_NUM,
} TX_CHANNELS_SOURCE_ENUM;


typedef enum {
    IN_CONFIG_SBUS = 0,
    IN_CONFIG_SBUS_INVERTED,
    IN_CONFIG_NUM,
} TX_IN_CONFIG_ENUM;


typedef enum {
    CLI_LINE_END_CR = 0,
    CLI_LINE_END_LF,
    CLI_LINE_END_CRLF,
    CLI_LINE_END_NUM,
} TX_CLI_LINE_END_ENUM;


typedef enum {
    BUZZER_OFF = 0,
    BUZZER_LOST_PACKETS,
    BUZZER_RX_LQ,
    BUZZER_NUM,
} TX_BUZZER_END_ENUM;


//-- Rx only

typedef enum {
    OUT_CONFIG_SBUS = 0,
    OUT_CONFIG_CRSF,
    OUT_CONFIG_SBUS_INVERTED,
    OUT_CONFIG_NUM,
} RX_OUT_CONFIG_ENUM;


typedef enum {
    OUT_RSSI_CHANNEL_OFF = 0,
    OUT_RSSI_CHANNEL_CH5,
    OUT_RSSI_CHANNEL_CH6,
    OUT_RSSI_CHANNEL_CH7,
    OUT_RSSI_CHANNEL_CH8,
    OUT_RSSI_CHANNEL_CH9,
    OUT_RSSI_CHANNEL_CH10,
    OUT_RSSI_CHANNEL_CH11,
    OUT_RSSI_CHANNEL_CH12,
    OUT_RSSI_CHANNEL_NUM,
} RX_OUT_RSSI_CHANNEL_ENUM;


typedef enum {
    FAILSAFE_MODE_NO_SIGNAL = 0,
    FAILSAFE_MODE_LOW_THROTTLE,
    FAILSAFE_MODE_AS_CONFIGURED,
    FAILSAFE_MODE_LOW_THROTTLE_ELSE_CENTER,
    FAILSAFE_MODE_CH1CH4_CENTER,
    FAILSAFE_MODE_NUM,
} RX_FAILSAFE_MODE_ENUM;


typedef enum {
    SEND_RC_CHANNELS_OFF = 0,
    SEND_RC_CHANNELS_OVERRIDE,
    SEND_RC_CHANNELS_RCCHANNELS,
    SEND_RC_CHANNELS_NUM,
} RX_SEND_RCCHANNELS_ENUM;


//-------------------------------------------------------
// Config Enums
//-------------------------------------------------------
// numbers must match config arrays in sx drivers !!

typedef enum {
    SX128x_LORA_CONFIG_BW800_SF5_CRLI4_5 = 0,
    SX128x_LORA_CONFIG_BW800_SF6_CRLI4_5,
    SX128x_LORA_CONFIG_BW800_SF7_CRLI4_5,
    SX128x_LORA_CONFIG_NUM,
} SX128x_LORA_CONFIG_ENUM;


typedef enum {
    SX127x_LORA_CONFIG_BW500_SF6_CR4_5 = 0,
    SX127x_LORA_CONFIG_NUM,
} SX127x_LORA_CONFIG_ENUM;


typedef enum {
    SX126x_LORA_CONFIG_BW500_SF5_CR4_5 = 0,
    SX126x_LORA_CONFIG_BW500_SF6_CR4_5,
    SX126x_LORA_CONFIG_NUM,
} SX126x_LORA_CONFIG_ENUM;


//-------------------------------------------------------
// Setup and Config Types
//-------------------------------------------------------

typedef struct
{
    uint8_t Power;
    uint8_t Diversity;
    uint8_t ChannelsSource;
    uint8_t ChannelOrder;
    uint8_t InMode;
    uint8_t SerialDestination;
    uint8_t SerialBaudrate;
    uint8_t SerialLinkMode;
    uint8_t SendRadioStatus;
    uint8_t Buzzer;
    uint8_t CliLineEnd;

    uint8_t spare[9];
} tTxSetup; // 20 bytes


typedef struct
{
    uint8_t Power;
    uint8_t Diversity;
    uint8_t ChannelOrder;
    uint8_t OutMode;
    uint8_t OutRssiChannelMode;
    uint8_t FailsafeMode;
    uint8_t SerialBaudrate;
    uint8_t SerialLinkMode;
    uint8_t SendRadioStatus;
    uint8_t Buzzer;
    uint8_t SendRcChannels;
    uint8_t RadioStatusMethod;

    uint8_t spare[8];

    int8_t FailsafeOutChannelValues_Ch1_Ch12[12]; // -120 .. +120
    uint8_t FailsafeOutChannelValues_Ch13_Ch16[4]; // 0,1,2 = -120, 0, +120
} tRxSetup; // 36 bytes


#define SETUP_MARKER_STR      "SetupStartMarker"
#define SETUP_MARKEREND_STR   "!end!"

// user setable parameter values, stored in EEPROM
typedef struct
{
    char MarkerStr[16];
    uint32_t Version;
    uint16_t Layout;

    // parameters common to both Tx and Rx
    // cannot be changed on the fly, loss of connection will happen, need restart/reconnect
    char BindPhrase[6+1];
    uint8_t FrequencyBand;
    uint8_t Mode;

    uint8_t spare[7];

    // parameters specific to Rx, can be changed on the fly
    tRxSetup Rx;

    // parameters specific to Tx, can be changed on the fly
    tTxSetup Tx;

    char MarkerEnd[8];
} tSetup;


typedef struct
{
    uint16_t FrequencyBand_allowed_mask;
    uint16_t Mode_allowed_mask;

    char Tx_Power_optstr[44+1];
    uint16_t Tx_Diversity_allowed_mask;
    uint16_t Tx_ChannelsSource_allowed_mask;
    uint16_t Tx_InMode_allowed_mask;
    uint16_t Tx_SerialDestination_allowed_mask;
    uint16_t Tx_Buzzer_allowed_mask;

    char Rx_Power_optstr[44+1];
    uint16_t Rx_Diversity_allowed_mask;
    uint16_t Rx_OutMode_allowed_mask;
    uint16_t Rx_Buzzer_allowed_mask;

    bool rx_available;

    uint32_t rx_firmware_version;
    uint16_t rx_setup_layout;
    char rx_device_name[20+1];
    int8_t rx_actual_power_dbm;
    uint8_t rx_actual_diversity;
} tSetupMetaData;


// global configuration values, not stored in EEPROM
// can be/are derived from setup parameters, from defines, or otherwise
typedef struct
{
    uint8_t Mode;

    uint8_t LoraConfigIndex;
    uint8_t lora_send_frame_tmo;

    uint16_t FrameSyncWord;
    uint16_t FhssNum;
    uint32_t FhssSeed;

    uint16_t LQAveragingPeriod;

    int8_t Power_dbm;
    uint32_t SerialBaudrate;

    uint16_t frame_rate_ms;
    uint16_t frame_rate_hz;
    uint16_t connect_tmo_systicks;
    uint16_t connect_listen_hop_cnt;

    bool UseAntenna1;
    bool UseAntenna2;

    bool UseMbridge;
    bool UseCrsf;
} tGlobalConfig;


//-------------------------------------------------------
// Defines
//-------------------------------------------------------

#define SEND_FRAME_TMO            Config.lora_send_frame_tmo

#define CONNECT_TMO_SYSTICKS      Config.connect_tmo_systicks
#define CONNECT_LISTEN_HOP_CNT    Config.connect_listen_hop_cnt


#endif // SETUP_TYPES_H

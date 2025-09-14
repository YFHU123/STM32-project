# STM32 IoT Remote Monitoring System

## 项目简介
本项目基于 STM32 单片机，使用 DHT11 传感器采集环境温湿度数据，通过 ESP8266 模块联网，将数据通过 **MQTT 协议**上传至 OneNote 或其他云平台。  
同时，用户可以通过手机 APP 实现远程控制灯的开关，实现 **物联网远程监控与控制** 功能。

---

## 功能特点
- STM32 采集 DHT11 温湿度数据  
- ESP8266 连接 Wi-Fi，实现联网功能  
- 使用 MQTT 协议上传数据到云端（如 OneNote）  
- 手机 APP 实现远程开关灯  
- 简单易扩展，可增加其他传感器或控制设备

---

## 硬件需求
- **STM32** 单片机开发板（如 STM32F103）  
- **DHT11** 温湿度传感器  
- **ESP8266** Wi-Fi 模块  
- **LED 灯** 或其他继电器控制设备  
- 若干连接线、电阻等基础电子元件  

---

## 软件需求
- STM32 IDE（Keil、EIDE、VSCode+PlatformIO 均可）  
- Arduino IDE / ESP8266 库（可编程 ESP8266）  
- MQTT Broker（如 HiveMQ、EMQX 或自建服务器）  
- 手机 APP 支持 MQTT 控制（如 **IoT MQTT Panel**, **Blynk**）

---

## 系统架构

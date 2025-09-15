# ESP32 Keyboard Bridge

This project turns an **ESP32** into a wireless keyboard input bridge.  
You can type text or send special keys from a web interface hosted by the ESP32,  
and a Python script on your PC types them out automatically using `pyautogui`.

---

## 🚀 Features
- ESP32 runs in **WiFi Access Point mode**
- Web interface for entering text or keys
- Text is URL-encoded and sent over serial
- Python script decodes & types it on the PC
- Supports typing in chunks for large text
- Supports special keys (`Enter`, `Backspace`, `Tab`, `Esc`, `Arrow Keys`)

---

## 📂 Repository Structure

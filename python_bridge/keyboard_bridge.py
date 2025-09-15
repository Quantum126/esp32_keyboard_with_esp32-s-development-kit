import serial
import pyautogui
import urllib.parse

ser = serial.Serial("COM3", 115200, timeout=0.2)
print("Keyboard Bridge Started...")

buffer = ""
while True:
    try:
        line = ser.readline().decode("utf-8", errors="ignore").strip()
        if not line:
            continue

        if line.startswith("TEXT:"):
            buffer += line[5:]  # collect chunks

        elif line == "ENDTEXT":
            text = urllib.parse.unquote_plus(buffer)
            # chunked typing with small delay
            CHUNK_SIZE = 50
            for i in range(0, len(text), CHUNK_SIZE):
                pyautogui.typewrite(text[i:i+CHUNK_SIZE], interval=0.02)
            buffer = ""  # reset

        elif line.startswith("KEY:"):
            key = line[4:].lower()
            valid_keys = ["enter", "backspace", "tab", "esc", "up", "down", "left", "right"]
            if key in valid_keys:
                pyautogui.press(key)
            else:
                print("Unknown key:", key)

    except Exception as e:
        print("Error:", e)

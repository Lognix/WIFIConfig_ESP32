#ifndef HTML_CONTENT_H
#define HTML_CONTENT_H

const char* HTML_SETUP = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>WiFi SETUP</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            background-color: #f4f4f4;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            margin: 0;
        }
        form {
            background-color: #fff;
            padding: 20px;
            border-radius: 8px;
            box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
            width: 300px;
            box-sizing: border-box;
        }
        h2 {
            text-align: center;
            color: #333;
            margin-bottom: 20px;
        }
        form input[type="text"],
        form input[type="password"] {
            width: 100%;
            padding: 10px;
            margin-bottom: 15px;
            border: 1px solid #ccc;
            border-radius: 4px;
            font-size: 16px;
            box-sizing: border-box;
        }
        form input[type="text"]::placeholder,
        form input[type="password"]::placeholder {
            color: #999;
        }
        form input[type="submit"] {
            width: 100%;
            padding: 10px;
            background-color: #4CAF50;
            color: white;
            border: none;
            border-radius: 4px;
            font-size: 16px;
            cursor: pointer;
        }
        form input[type="submit"]:hover {
            background-color: #45a049;
        }
    </style>
</head>
<body>
    <form action="/connect" method="POST">
        <h2>Setup WiFi Connection</h2>
        <input type="text" id="ssid" name="ssid" placeholder="SSID" required>
        <input type="password" id="pass" name="pass" placeholder="Password" required>
        <input type="submit" value="Connect">
    </form>
</body>
</html>
)=====";


const char* HTML_INDEX = R"======(
    <!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>ESP32 Heap Monitor</title>
        <script>
            async function fetchHeapData() {
                try {
                    const response = await fetch('/heap');
                    const data = await response.text();
                    document.getElementById('heap-info').innerText = 'Free Heap: ' + data;
                } catch (error) {
                    console.error('Error:', error);
                }
            }

            setInterval(fetchHeapData, 2000);
            window.onload = fetchHeapData;
        </script>
    </head>
    <body>
        <h1>ESP32 Heap Monitor</h1>
        <p id="heap-info">Loading...</p>
    </body>
    </html>
  )======";

#endif
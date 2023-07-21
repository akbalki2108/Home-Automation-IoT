const char index_html[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
    <head>
        <title>ESP32 Web Control</title>
        <style>
            html {
                font-family: Arial;
                display: inline-block;
                text-align: center;
            }
            h2 {
                font-size: 3rem;
            }
            p {
                font-size: 1rem;
            }
            body {
                max-width: 800px;
                margin: 0px auto;
                padding-bottom: 25px;
            }
            /* mera code start */
            .container {
                margin-top: 3rem;
                display: flex;
                gap: 2rem;
            }
            .first__main {
                flex: 2;
                display: flex;
                flex-wrap: wrap;
                align-items: center;
                justify-content: center;
                box-shadow: rgba(60, 64, 67, 0.3) 0px 1px 2px 0px,
                    rgba(60, 64, 67, 0.15) 0px 1px 3px 1px;
            }
            .first__main > * {
                min-width: 150px;
                max-height: 150px;
            }
            .second_main {
                flex: 1;
                display: flex;
                flex-direction: column;
                gap: 2rem;
            }
            .second_main > * {
                margin: 0;
                padding: 1rem;
                box-shadow: rgba(60, 64, 67, 0.3) 0px 1px 2px 0px,
                    rgba(60, 64, 67, 0.15) 0px 1px 3px 1px;
            }

            /* mera code end */

            .switch {
                position: relative;
                display: inline-block;
                width: 120px;
                height: 68px;
            }
            .switch input {
                display: none;
            }
            .slider {
                position: absolute;
                top: 0;
                left: 0;
                right: 0;
                bottom: 0;
                background-color: #ccc;
                border-radius: 34px;
            }
            .slider:before {
                position: absolute;
                content: "";
                height: 52px;
                width: 52px;
                left: 8px;
                bottom: 8px;
                background-color: #fff;
                -webkit-transition: 0.4s;
                transition: 0.4s;
                border-radius: 68px;
            }
            input:checked + .slider {
                background-color: #2196f3;
            }
            input:checked + .slider:before {
                -webkit-transform: translateX(52px);
                -ms-transform: translateX(52px);
                transform: translateX(52px);
            }
            svg {
                height: 30px;
                width: 30px;
            }
        </style>
        <script>
            function toggleLed(element, led) {
                var xhr = new XMLHttpRequest();
                if (element.checked) {
                    xhr.open(
                        "GET",
                        "/led" + led + "Update" + "?state" + led + "=1",
                        true
                    );
                } else {
                    xhr.open(
                        "GET",
                        "/led" + led + "Update" + "?state" + led + "=0",
                        true
                    );
                }
                xhr.send();
            }
            
            function toggleFan(element,fan) {
                var xhr = new XMLHttpRequest();
                if (element.checked) {
                    xhr.open(
                      "GET",
                      "/fan" + fan + "Update" + "?state" + fan + "=1",
                      true
                    );
                } else {
                  xhr.open(
                    "GET",
                    "/fan" + fan + "Update" + "?state" + fan + "=0",
                    true
                  );
                }
                xhr.send();
            }
            
        </script>
    </head>
    <body>
        <h1>ESP32 Web Control</h1>
        <div class="container">
            <div class="first__main">
                <div>
                    <label for="led1" class="switch">
                        <input
                            type="checkbox"
                            id="led1"
                            onchange="toggleLed(this,1)"
                        />
                        <span class="slider"></span>
                    </label>
                    <h4>LED 1 - State <span id="led1status"></span></h4>
                </div>

                <div>
                    <label for="led2" class="switch">
                        <input
                            type="checkbox"
                            id="led2"
                            onchange="toggleLed(this,2)"
                        />
                        <span class="slider"></span>
                    </label>
                    <h4>LED 2 - State <span id="led2status"></span></h4>
                </div>

                <div>
                    <label for="led3" class="switch">
                        <input
                            type="checkbox"
                            id="led3"
                            onchange="toggleLed(this,3)"
                        />
                        <span class="slider"></span>
                    </label>
                    <h4>LED 3 - State <span id="led3status"></span></h4>
                </div>

                <div>
                    <label for="fan1" class="switch">
                        <input
                            type="checkbox"
                            id="fan1"
                            onchange="toggleFan(this,1)"
                        />
                        <span class="slider"></span>
                    </label>
                    <h4>FAN 1 - State <span id="fan1status"></span></h4>
                </div>

                <div>
                    <label for="fan2" class="switch">
                        <input
                            type="checkbox"
                            id="fan2"
                            onchange="toggleFan(this,2)"
                        />
                        <span class="slider"></span>
                    </label>
                    <h4>FAN 2 - State <span id="fan2status"></span></h4>
                </div>
            </div>

            <div class="second_main">
                <div>
                    <svg
                        viewBox="0 0 24 24"
                        fill="none"
                        xmlns="http://www.w3.org/2000/svg"
                    >
                        <g id="SVGRepo_bgCarrier" stroke-width="0"></g>
                        <g
                            id="SVGRepo_tracerCarrier"
                            stroke-linecap="round"
                            stroke-linejoin="round"
                        ></g>
                        <g id="SVGRepo_iconCarrier">
                            <path
                                d="M11 12H21M5 4V20M5 4L8 7M5 4L2 7M5 20L8 17M5 20L2 17M11 6H21M11 18H21"
                                stroke="#000000"
                                stroke-width="2"
                                stroke-linecap="round"
                                stroke-linejoin="round"
                            ></path>
                        </g>
                    </svg>
                    <h3>Ultrasonic Sensor</h3>
                    <div>
                        <label for="distance">Distance:</label>
                        <span id="distance"></span> cm
                    </div>
                </div>
                <div>
                    <svg
                        fill="#000000"
                        width="256px"
                        height="256px"
                        viewBox="-2.56 -2.56 37.12 37.12"
                        version="1.1"
                        xmlns="http://www.w3.org/2000/svg"
                        stroke="#000000"
                        stroke-width="0.00032"
                    >
                        <g id="SVGRepo_bgCarrier" stroke-width="0"></g>
                        <g
                            id="SVGRepo_tracerCarrier"
                            stroke-linecap="round"
                            stroke-linejoin="round"
                        ></g>
                        <g id="SVGRepo_iconCarrier">
                            <title>temperature-half</title>
                            <path d="M21.25 6.008c0-6.904-10.5-6.904-10.5 0v13.048c-1.238 1.298-2.001 3.061-2.001 5.001 0 4.004 3.246 7.25 7.25 7.25s7.25-3.246 7.25-7.25c0-1.94-0.762-3.702-2.003-5.003l0.003 0.003zM16 28.75c-2.623 0-4.75-2.127-4.75-4.75 0-1.405 0.61-2.667 1.58-3.537l0.004-0.004c0.009-0.008 0.013-0.020 0.022-0.029 0.059-0.063 0.112-0.133 0.157-0.208l0.003-0.006c0.043-0.053 0.084-0.113 0.119-0.175l0.003-0.006c0.020-0.055 0.037-0.122 0.049-0.19l0.001-0.007c0.027-0.081 0.047-0.175 0.056-0.272l0-0.005 0.007-0.033v-13.52c-0.001-0.031-0.002-0.068-0.002-0.105 0-1.52 1.232-2.752 2.752-2.752s2.752 1.232 2.752 2.752c0 0.037-0.001 0.074-0.002 0.11l0-0.005v13.52c0 0.012 0.007 0.023 0.007 0.035 0.009 0.098 0.028 0.188 0.056 0.274l-0.002-0.009c0.013 0.079 0.031 0.149 0.055 0.217l-0.003-0.009c0.038 0.068 0.079 0.127 0.123 0.182l-0.002-0.002c0.048 0.081 0.101 0.151 0.16 0.215l-0.001-0.001c0.009 0.009 0.012 0.021 0.022 0.029 0.974 0.874 1.584 2.136 1.584 3.541 0 2.623-2.127 4.75-4.75 4.75v0zM17.25 21.001v-7.5c0-0.69-0.56-1.25-1.25-1.25s-1.25 0.56-1.25 1.25v0 7.5c-1.184 0.503-2 1.656-2 3 0 1.795 1.455 3.25 3.25 3.25s3.25-1.455 3.25-3.25c0-1.344-0.816-2.497-1.979-2.992l-0.021-0.008zM26.5 1.75c-2.071 0-3.75 1.679-3.75 3.75s1.679 3.75 3.75 3.75c2.071 0 3.75-1.679 3.75-3.75v0c-0.002-2.070-1.68-3.748-3.75-3.75h-0zM26.5 6.75c-0.69 0-1.25-0.56-1.25-1.25s0.56-1.25 1.25-1.25c0.69 0 1.25 0.56 1.25 1.25v0c-0.001 0.69-0.56 1.249-1.25 1.25h-0z"
                            ></path>
                        </g>
                    </svg>
                    <h3>Temperature Sensor</h3>
                    <div>
                        <label for="temp">Temperature:</label>
                        <span id="temp"></span>ºC
                    </div>
                </div>
                <div>
                    <svg
                        width="243px"
                        height="243px"
                        viewBox="0 0 24 24"
                        fill="none"
                        xmlns="http://www.w3.org/2000/svg">
                        <g id="SVGRepo_bgCarrier" stroke-width="0"></g>
                        <g
                            id="SVGRepo_tracerCarrier"
                            stroke-linecap="round"
                            stroke-linejoin="round">
                        </g>
                        <g id="SVGRepo_iconCarrier">
                            <path
                                d="M12 12.5H6V13.5H12V12.5ZM18 12.5H12V13.5H18V12.5ZM20.5 10C20.5 11.3807 19.3807 12.5 18 12.5V13.5C19.933 13.5 21.5 11.933 21.5 10H20.5ZM18 7.5C19.3807 7.5 20.5 8.61929 20.5 10H21.5C21.5 8.067 19.933 6.5 18 6.5V7.5ZM17.0201 5.75007C16.1607 3.83526 14.2368 2.5 12 2.5V3.5C13.8287 3.5 15.4038 4.59089 16.1078 6.15954L17.0201 5.75007ZM12 2.5C9.76317 2.5 7.83928 3.83526 6.97989 5.75007L7.89222 6.15954C8.59624 4.59089 10.1713 3.5 12 3.5V2.5ZM6 6.5C4.067 6.5 2.5 8.067 2.5 10H3.5C3.5 8.61929 4.61929 7.5 6 7.5V6.5ZM2.5 10C2.5 11.933 4.067 13.5 6 13.5V12.5C4.61929 12.5 3.5 11.3807 3.5 10H2.5ZM6.97989 5.75007C6.77146 6.21449 6.38469 6.5 6 6.5V7.5C6.89538 7.5 7.57652 6.86297 7.89222 6.15954L6.97989 5.75007ZM18 6.5C17.6153 6.5 17.2285 6.21449 17.0201 5.75007L16.1078 6.15954C16.4235 6.86297 17.1046 7.5 18 7.5V6.5Z"
                                fill="#222222"
                            ></path>
                            <path
                                d="M12 19V17"
                                stroke="#222222"
                                stroke-linecap="round"
                            ></path>
                            <path
                                d="M17 20V17"
                                stroke="#222222"
                                stroke-linecap="round"
                            ></path>
                            <path
                                d="M7 21V17"
                                stroke="#222222"
                                stroke-linecap="round"
                            ></path>
                        </g>
                    </svg>
                    <h3>DHT11 Sensor</h3>
                    <div>
                        <label for="humi">Humidity:</label>
                        <span id="humi"></span> 
                    </div>
                </div>
            </div>
        </div>

        <script>
            function getStatus() {
                var xhr = new XMLHttpRequest();
                xhr.open("GET", "/status");
                xhr.responseText = "text";
                xhr.onreadystatechange = function () {
                    if (this.readyState == 4 && this.status == 200) {
                        // console.log(xhr.response);
                        console.log(xhr.responseText);
                        // console.log(typeof xhr.response);

                        var status = JSON.parse(xhr.responseText);
                        // console.log(status.led1);
                        if (status.led1 === "ON") {
                            document.getElementById("led1").checked = true;
                            document.getElementById("led1status").innerHTML =
                                status.led1;
                        } else {
                            document.getElementById("led1").checked = false;
                            document.getElementById("led1status").innerHTML =
                                status.led1;
                        }

                        if (status.led2 === "ON") {
                            document.getElementById("led2").checked = true;
                            document.getElementById("led2status").innerHTML =
                                status.led2;
                        } else {
                            document.getElementById("led2").checked = false;
                            document.getElementById("led2status").innerHTML =
                                status.led2;
                        }

                        if (status.led3 === "ON") {
                            document.getElementById("led3").checked = true;
                            document.getElementById("led3status").innerHTML =
                                status.led3;
                        } else {
                            document.getElementById("led3").checked = false;
                            document.getElementById("led3status").innerHTML =
                                status.led3;
                        }

                        if (status.fan1 === "ON") {
                            document.getElementById("fan1").checked = true;
                            document.getElementById("fan1status").innerHTML = status.fan1;
                        } else {
                            document.getElementById("fan1").checked = false;
                            document.getElementById("fan1status").innerHTML = status.fan1;
                        }

                        if (status.fan2 === "ON") {
                            document.getElementById("fan2").checked = true;
                            document.getElementById("fan2status").innerHTML = status.fan2;
                        } else {
                            document.getElementById("fan2").checked = false;
                            document.getElementById("fan2status").innerHTML = status.fan2;
                        }
                    }
                };
                xhr.send();
            }

            function updateDHT11() {
                var xhr = new XMLHttpRequest();
                xhr.open("GET", "/dht11");
                xhr.responseText = "text";
                xhr.onreadystatechange = function () {
                    if (this.readyState == 4 && this.status == 200) {
                      var status = JSON.parse(xhr.responseText);
                      document.getElementById("temp").innerHTML = status.temp;
                      document.getElementById("humi").innerHTML = status.humi;
                    }
                };
                xhr.send();
            }

            function updateDistance(distance) {
                document.getElementById("distance").innerHTML = distance;
            }

            function updateSensor() {
                var xhr = new XMLHttpRequest();
                xhr.open("GET", "/distance", true);
                xhr.onload = function () {
                    if (this.status == 200) {
                        updateDistance(this.responseText);
                    }
                };
                xhr.send();
            }

            //setInterval(getLedStatus,1000);

            setInterval(function () {
                getStatus();
                updateSensor();
                updateDHT11();
            }, 1000);
        </script>
    </body>
</html>
)=====";

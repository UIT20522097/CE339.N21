import json
import requests
import time
from flask import Flask, render_template, request
from flask_mqtt import Mqtt
app = Flask(__name__, template_folder='templates')

# Cấu hình kết nối tới broker
app.config['MQTT_BROKER_URL'] = 'mqtt3.thingspeak.com'
app.config['MQTT_BROKER_PORT'] = 1883
app.config["MQTT_TRANSPORT"] = "TCP"
app.config['MQTT_USERNAME'] = 'IgAhECIoJjcSHhwwCR49DTs'
app.config['MQTT_CLIENT_ID'] = 'IgAhECIoJjcSHhwwCR49DTs'
app.config['MQTT_PASSWORD'] = 'omKdOVvpxyI2Cmh4wDOYNe4R'
app.config['MQTT_KEEPALIVE'] = 60
app.config['MQTT_CLEAN_SESSION'] = True
app.config['MQTT_REFRESH_TIME'] = 5.0 # refresh time in seconds
# Khởi tạo đối tượng MQTT
mqtt = Mqtt(app, connect_async=True)
mqtt.init_app(app)
topic6 = "channels/2173391/publish/fields/field6"
topic1 = "channels/2173391/publish/fields/field1"






def get_data(number_of_data=20):
    # URL của endpoint hoặc API
    url = f'https://api.thingspeak.com/channels/2173391/fields/6.json?results={number_of_data}'

    # Thực hiện yêu cầu GET để lấy dữ liệu từ server
    response = requests.get(url)

    # Kiểm tra mã trạng thái của phản hồi
    if response.status_code == 200:  # Mã trạng thái 200 đại diện cho thành công
        # Lấy dữ liệu từ phản hồi dưới dạng JSON
        data = response.json()

        # Xử lý dữ liệu theo nhu cầu của bạn
        # Ví dụ: lấy giá trị của trường "field1" trong dữ liệu
        field1_values = [feed['field6'] for feed in data['feeds']]

        # In ra giá trị của trường "field1"
        print(field1_values)
        return field1_values[-1]
    else:
        return get_data()

# Lấy dữ liệu từ ThingSpeak
fan_status = get_data(1)

def publish_topic(topic, data, qos=0):
    results, mid = mqtt.publish(topic, data, qos=qos)
    print(results, mid)
    if results == 0:
        print("Message published successfully")
    else:
        time.sleep(1)
        return publish_topic(topic, data, qos=qos)
    return "OK"

@mqtt.on_connect()
def handle_connect(client, userdata, flags, rc):
    mqtt.subscribe(topic6)
    print('Connected to MQTT broker')

@mqtt.on_message()
def handle_message(client, userdata, message):
    topic = message.topic
    payload = message.payload.decode('utf-8')
    print(f'Received message: {payload} on topic: {topic}')
    if topic == topic6:
        global fan_status
        fan_status = payload
        print(fan_status)


@app.route('/')
def index():
    return render_template('index.html')

@app.route('/chart', methods=['GET'])
def chart():
    data = get_data()
    return data

@app.route('/temperaturenow', methods=['GET'])
def temperaturenow():
    data = get_data(1)
    return data

@app.route('/fan', methods=['POST'])
def fan():
    data = request.data.decode('utf-8')
    print('\n')
    print(data)
    global fan_status
    if data == '1':
        fan_status = '1'
        publish_topic(topic6, '1', qos=0)
    else:
        if data == '0':
            fan_status = '0'
            publish_topic(topic6, '0', qos=0)
        else:
            return "ERROR"

    return "OK"

@app.route('/fanstatus', methods=['GET'])
def fanstatus():
    return fan_status

###################################################################################
if __name__ == '__main__':
    app.run(host="192.168.0.197" ,port=3001, debug=True)

###################################################################################




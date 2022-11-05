from influxdb import InfluxDBClient
from datetime import datetime 
row = []

client = InfluxDBClient(host='192.168.178.83', port=8086)
client.switch_database("water_meter")

def parse_row(row: str):
    items = row.split(",")
    # line protocol: time,wtemp,ltemp,photo_r1,photo_r2,hal_flow,hal_depth
    time = items[0]
    point = {
        "measurement": "water_meter",
        "time": datetime.fromtimestamp(int(time)),
        "fields": {
            "wtemp": float(items[1]) / 1000,
            "ltemp": float(items[2]) / 1000,
            "photo_r1": int(items[3]),
            "photo_r2": int(items[4]),
            "hal_flow": int(items[5]),
            "hal_depth": int(items[6]),
        }
    }
    print(point)
    client.write_points(points=[point])    

with open("input.txt") as file:
    lines = file.readlines()
    for line in lines:
        parse_row(line)

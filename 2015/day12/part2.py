import json


def handle_object(obj):
    sum = 0

    for value in list(obj):
        if value == "red":
            return 0
        else:
            block = obj[value]

            if block == "red":
                return 0
            if type(block) is int:
                sum = sum + block
            if type(block) is dict:
                sum = sum + handle_object(block)
            if type(block) is list:
                sum = sum + handle_array(block)

    return sum


def handle_array(data):
    sum = 0

    for block in data:
        if type(block) is int:
            sum = sum + block
        if type(block) is dict:
            sum = sum + handle_object(block)
        if type(block) is list:
            sum = sum + handle_array(block)

    return sum


sum = 0
full = json.JSONDecoder().decode(open("input", 'r').read())

if type(full) is dict:
    sum = sum + handle_object(full)
if type(full) is list:
    sum = sum + handle_array(full)

print(sum)

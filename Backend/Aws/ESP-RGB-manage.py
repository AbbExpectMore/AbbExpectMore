import json
import boto3
import datetime

dynamodb = boto3.resource('dynamodb', region_name='us-east-1')


def checkbody(body):

    if "id" not in body:
        return [False, "id"]

    if "action" not in body:
        return [False, "action"]

    if "value" not in body:
        return [False, "value"]

    if type(body["value"]) != bool:
        return [False, "bool"]

    return [True]


def checkid(body):
    table = dynamodb.Table('Users')

    result = table.get_item(
        Key={
            'username': "admin",

        }
    )

    if "Item" not in result:  # avslutar om användaren inte finns
        return [False, "No user"]

    if result["Item"]["id"] == body["id"]:  # om det stämmer överäns
        return [True]
    else:
        return [False, "No user"]


def addto(body):

    table = dynamodb.Table('ESP-RGB')

    result = table.get_item(
        Key={
            'name': "ESP-RGB",
        }
    )
    
    res = result["Item"]
    
    if body["action"] == "lock":
        
        response = table.put_item(
            Item={
                'name': res["name"],
                'Locked': str(bool(body["value"])).lower(),
                'Log': res["Log"]
            }
        )
        

    # currentAmount = result["Item"]["CurrentAmount"]

    # # result["Item"]["LastAmount"][0] = int(result["Item"]["LastAmount"][0])
    # result["Item"]["CurrentAmount"] = int(result["Item"]["CurrentAmount"])

    # result["Item"]["LastAmount"].append(int(body["Amount"]))
    # result["Item"]["LastUpdate"].append(str(datetime.datetime.now()))

    # # print(result["Item"])

    # response = table.put_item(
    #     Item={
    #         'Skola': Skola,
    #         'Ansvarig': result["Item"]["Ansvarig"],

    #         'LastUpdate': result["Item"]["LastUpdate"],
    #         'LastAmount': result["Item"]["LastAmount"],
    #         'CurrentAmount': (body["Amount"] + currentAmount),
    #     }
    # )

def lambda_handler(event, context):
    
    try:
        body = json.loads(event["body"])
    except Exception:
        return {
            'statusCode': 201,
            'headers': {
                    'Content-Type': 'application/json',
                    "Access-Control-Allow-Origin": "*" 
            },
            'body': json.dumps({
                "Success": False,
                "Meddelande": "No body!"
            })
        }
    
    # body = event["body"]
        
    # print(type(checkbody(body)))

    if checkbody(body)[0] == False:  # Hittade inte Skola, id eller Amount

        if checkbody(body)[1] == "int":
            return {
                'statusCode': 201,
                'headers': {
                        'Content-Type': 'application/json',
                        "Access-Control-Allow-Origin": "*" 
                },
                'body': json.dumps({
                    "Success": False,
                    "Meddelande": "'Amount' isn't a int!"
                })
            }

        return {
            'statusCode': 201,
            'headers': {
                    'Content-Type': 'application/json',
                    "Access-Control-Allow-Origin": "*" 
            },
            'body': json.dumps({
                "Success": False,
                "Meddelande": "Ingen '" + checkbody(body)[1] + "' i body!"
            })
        }

    if (check := checkid(body))[0] == False:  # Hittade inte användaren
        # print(check)
        return {
            'statusCode': 201,
            'headers': {
                    'Content-Type': 'application/json',
                    "Access-Control-Allow-Origin": "*" 
            },
            'body': json.dumps({
                "Success": False,
                "Meddelande": "Hittade inte användaren!"
            })
        }


    addto(body)

    return {
        'statusCode': 200,
        'headers': {
                'Content-Type': 'application/json',
                "Access-Control-Allow-Origin": "*" 
        },
        'body': json.dumps({
            "Success": True,
            "Meddelande": "Uppdaterade Värdet!"
        })
    }

import json
import boto3

dynamodb = boto3.resource('dynamodb', region_name='us-east-1')

def lambda_handler(event, context):
    
    
    # return {
    #     'statusCode': 200,
    #     'headers': {
    #         'Content-Type': 'application/json',
    #         "Access-Control-Allow-Origin": "*" 
    #     },
    #     'body': json.dumps({
    #         "Debug": event})
    # }

    table = dynamodb.Table('ESP-RGB')

    result = table.get_item(
        Key={
            'name': "ESP-RGB",
        }
    )
    # print(result["Item"])
    
    if result["Item"]["Locked"] == "false":
        res = False
    else:
        res = True
        
    try:
        Last_val = result["Item"]["Last_val"]
    except:
        Last_val = result["Item"]["Log"][-1][0]
        
    
    return {
        'statusCode': 200,
        'headers': {
            'Content-Type': 'application/json',
            "Access-Control-Allow-Origin": "*" 
        },
        'body': json.dumps({
            "locked": res,
            "Last_val": Last_val
            })
    }
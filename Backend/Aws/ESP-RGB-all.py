import json
import boto3

dynamodb = boto3.resource('dynamodb', region_name='us-east-1')

def lambda_handler(event, context):
    
    table = dynamodb.Table('ESP-RGB')

    result = table.get_item(
        Key={
            'name': "ESP-RGB",
        }
    )
    
    return {
        'statusCode': 200,
        'headers': {
            'Content-Type': 'application/json',
            "Access-Control-Allow-Origin": "*" 
        },
        'body': json.dumps(result["Item"]["Log"])
    }

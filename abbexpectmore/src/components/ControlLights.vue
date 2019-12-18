<template>
  <v-container>
    <v-layout text-center wrap>
      <v-flex xs12>
        <v-form>
          <v-text-field dark v-model="user" label="Username" required></v-text-field>
          <v-text-field dark v-model="pass" label="Password" type="password" required></v-text-field>
          <v-text-field dark v-model="message" label="Message" required></v-text-field>
          <v-btn dark :disabled="Boolean(connected)" @click="connect()">Connect</v-btn>
          <v-btn dark :disabled="!Boolean(connected)" @click="send()">Send</v-btn>
          <v-btn dark @click="test()">Test</v-btn>
          <v-alert :type="Alert_type" v-if="Alert">{{ Alert_text }}</v-alert>
        </v-form>
      </v-flex>
    </v-layout>
  </v-container>
</template>

<script>
var mqtt = require("mqtt"),
  url = require("url");

export default {
  name: "ControlLights",

  data: () => ({
    counter: 0,
    connected: false,
    client: undefined,
    user: "lisa.engstrom@abbindustrigymnasium.se",
    pass: "Hugoma02",
    message: "",
    Alert: false,
    Alert_type: "warning",
    Alert_text: "Could not connect to broker :(("
  }),
  methods: {
    connect() {
      var mqtt_url = "maqiatto.com";
      var url = "mqtt://" + mqtt_url;
      var options = {
        port: 8883,
        clientId:
          "mqttjs_" +
          Math.random()
            .toString(16)
            .substr(2, 8),
        username: this.user,
        password: this.pass
      };

      // user = this.options.username
      // pass = this.options.password
      console.log("connecting");
      this.client = mqtt.connect(url, options);
      console.log("connected?");

      this.client
        .on("error", function(error) {
          console.log("no");
          this.Alert = true;
          this.connected = false;
          console.log(this.Alert, this.connected);
        })
        .on("close", function(error) {
          console.log("no");
          this.Alert = true;
          this.connected = false;
        });
      this.connected = true;
    },
    send() {
      this.client.publish(
        "lisa.engstrom@abbindustrigymnasium.se/mess",
        this.message
      );
    },
    test(){
      console.log(this.Alert)
    }
  }
};
</script>

<style>
#Body {
  color: rgb(255, 255, 255);
  font-size: 20px;
}
</style>

<template>
  <v-row align="start" justify="space-around" no-gutters>
    <v-col cols="4">
      <!-- <v-flex xs12> -->
      <v-card dark class="ma-4 grey darken-3">
        <v-form class="ma-4 pa-3">
          <v-text-field dark v-model="user" label="Username" required></v-text-field>
          <v-text-field dark v-model="pass" label="Password" type="password" required></v-text-field>
          <v-row align="start" justify="space-around" no-gutters>
            <v-btn style="transform: scale(1.25)" dark :disabled="Boolean(connected)" @click="connect()">Connect</v-btn>
          </v-row>
          <!-- <p class="white--text">{{ mode || 'null' }}</p> -->
          <v-radio-group dark v-model="mode" :mandatory="false">
            <v-radio label="On/Off" value="On/Off"></v-radio>
            <v-radio label="Color Wheel" value="Color Wheel"></v-radio>
          </v-radio-group>
          <!-- <v-text-field v-if="mode == 'On/Off'" dark v-model="message" label="Message" required></v-text-field> -->
          <v-row align="start" justify="space-around" no-gutters>
            <v-switch
              :disabled="!Boolean(connected)"
              color="#f3952d"
              v-if="mode == 'On/Off'"
              v-model="switch1"
              style="transform: scale(2)"
              @change="ono()"
            ></v-switch>
          </v-row>

          <v-row align="start" justify="space-around" no-gutters>
          <color-picker v-model="color" v-if="mode == 'Color Wheel'"></color-picker>
          </v-row>
          <p dark v-if="mode == 'Color Wheel'">
            Color:
            <input v-model="color" type="text" />
          </p>

          <v-row align="start" justify="space-around" no-gutters>
            <v-btn
              v-if="mode == 'Color Wheel'"
              dark
              :disabled="!Boolean(connected)"
              @click="uValue()"
              style="transform: scale(1.25)"
            >Update</v-btn>
          </v-row>

          <v-alert :type="Alert_type" v-if="Alert">{{ Alert_text }}</v-alert>
        </v-form>
      </v-card>
      <!-- </v-flex> -->
    </v-col>
  </v-row>
</template>

<script>
import ColorPicker from "vue-color-picker-wheel";
var mqtt = require("mqtt"),
  url = require("url");

export default {
  name: "ControlLights",
  components: {
    ColorPicker
  },
  data: () => ({
    counter: 0,
    connected: false,
    client: undefined,
    user: "abbexpectmore@gmail.com",
    pass: "ABBExpectMore2020",
    message: "",
    Alert: false,
    Alert_type: "warning",
    Alert_text: "Could not connect to broker :((",
    value: undefined,
    mode: undefined,
    switch1: false,
    ch: 0,
    color: undefined,
    colorRgb: undefined
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
      this.client.publish("abbexpectmore@gmail.com/light", this.message);
    },
    ono() {
      if (this.switch1 == true) {
        this.client.publish("abbexpectmore@gmail.com/light", "on");
      } else {
        this.client.publish("abbexpectmore@gmail.com/light", "off");
      }
    },
    hex2rgb(hex) {
      var h = hex.replace("#", "");
      h = h.match(new RegExp("(.{" + h.length / 3 + "})", "g"));

      for (var i = 0; i < h.length; i++)
        h[i] = parseInt(h[i].length == 1 ? h[i] + h[i] : h[i], 16);

      return "(" + h.join(",") + ")";
    },
    uValue() {
      this.value = this.hex2rgb(this.color);
      this.client.publish("abbexpectmore@gmail.com/ctrl", this.value);
      console.log(this.value);
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

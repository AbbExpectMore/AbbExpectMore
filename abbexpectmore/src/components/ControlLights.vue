<template>
  <v-row align="start" justify="space-around" no-gutters>
    <v-col cols="auto">
      <!-- <v-flex xs12> -->
      <v-card v-if="this.$store.state.locked" dark class="ma-4 grey darken-3">
        <h1>This paged is locked</h1>
      </v-card>

      <!-- Normal Screen -->

      <v-card v-if="!this.$store.state.locked && !this.$store.state.connected" dark class="ma-4 grey darken-3">
        <v-form class="ma-4 pa-4">
          <v-text-field dark v-model="user" label="Username" required></v-text-field>
          <v-text-field dark v-model="pass" label="Password" type="password" required></v-text-field>
          <v-row align="start" justify="space-around" no-gutters>
            <v-btn style="transform: scale(1.25)" dark :disabled="this.$store.state.connected" @click="connect()">Connect</v-btn>
          </v-row>
        </v-form>
      </v-card>
      <v-card v-if="!this.$store.state.locked && this.$store.state.connected" dark class="pa-4 ma-4 grey darken-3">
        <colorpanel/>
      </v-card>
      <!-- </v-flex> -->
    </v-col>
  </v-row>
</template>

<script>
import ColorPicker from "vue-color-picker-wheel";
import { mapGetters } from "vuex";

var mqtt = require("mqtt"),
  url = require("url");

export default {
  name: "ControlLights",
  components: {
    //ColorPicker,
    colorpanel: () => import("@/components/color_panel.vue")
  },
  computed: {
      ...mapGetters([
          'locked'
      ])
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
        console.log('Connected!')
        this.$store.dispatch('connected')
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

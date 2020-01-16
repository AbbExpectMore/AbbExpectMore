<template>
  <v-row align="start" justify="space-around" no-gutters>
    <v-col cols="auto">
      <!-- <v-flex xs12> -->

      <!-- Normal Screen -->

          <v-radio-group dark v-model="mode" :mandatory="false">
            <v-radio label="On/Off" value="On/Off"></v-radio>
            <v-radio label="Color Wheel" value="Color Wheel"></v-radio>
            <v-radio label="Brightness" value="Brightness"></v-radio>
          </v-radio-group>
          <!-- <v-text-field v-if="mode == 'On/Off'" dark v-model="message" label="Message" required></v-text-field> -->
          <v-row align="start" justify="space-around" no-gutters>
            <v-switch
              :disabled="!this.$store.state.connected"
              color="#f3952d"
              v-if="mode == 'On/Off'"
              v-model="switch1"
              style="transform: scale(2)"
              @change="ono()"
            ></v-switch>
          </v-row>

          <v-row>
            <v-slider color="#f3952d" style="transform: scale(1.75)" v-if="mode == 'Brightness'"></v-slider>
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
              :disabled="!this.$store.state.connected"
              @click="uValue()"
              style="transform: scale(1.25)"
            >Update</v-btn>
          </v-row>

          <v-alert :type="Alert_type" v-if="Alert">{{ Alert_text }}</v-alert>
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
  name: "colorpanel",
  components: {
    ColorPicker
  },
  computed: {
      ...mapGetters([
          'locked',
          'connected'
      ])
  },
  data: () => ({
    counter: 0,
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

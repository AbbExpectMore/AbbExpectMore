<template>
  <v-row align="start" justify="space-around" no-gutters>
    <v-col cols="auto">
      <!-- Normal Screen -->

          <v-radio-group dark v-model="mode" :mandatory="false">
            <v-radio label="On/Off" value="On/Off"></v-radio>
            <v-radio label="Color Wheel" value="Color Wheel"></v-radio>
            <v-radio label="Brightness" value="Brightness"></v-radio>
          </v-radio-group>
          <v-row align="start" justify="space-around" no-gutters>
            <v-switch
              color="#f3952d"
              v-if="mode == 'On/Off'"
              v-model="switch1"
              style="transform: scale(1.75)"
              @change="ono()"
            ></v-switch>
          </v-row>

          <v-row align="start" justify="space-around" no-gutters v-if="mode == 'Brightness'">
              <v-slider color="#f3952d" v-model="bright"></v-slider>
          </v-row>
          <v-row align="start" justify="space-around" no-gutters v-if="mode == 'Brightness'">
          <v-btn @click="send()">
            Update
          </v-btn>
          </v-row>
          <v-row v-if="mode == 'Color Wheel'" align="start" justify="space-around" no-gutters>
            <ColorPicker />
          </v-row>
          <v-alert :type="Alert_type" v-if="Alert">{{ Alert_text }}</v-alert>
      <!-- </v-flex> -->
    </v-col>
  </v-row>
</template>

<script>
// import ColorPicker from "vue-color-picker-wheel";
import { mapGetters } from "vuex";
import axios from 'axios';
import ColorPicker from '@/components/ColorPicker.vue'
import { stringify } from 'querystring';

var mqtt = require("mqtt"),
  url = require("url");
export default {
  name: "colorpanel",
  components: {
    ColorPicker,
  },
  computed: {
      ...mapGetters([
          'locked',
          'connected',
          'onOff'
      ])
  },
  data: () => ({
    bright: undefined,
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
    colorRgb: undefined,
    ah: {
      method: undefined, //brightness
      value: undefined,
      pass: 'okokokok'
    }
  }),
  methods: {
    send() {
      this.ah.method = 'brightness'
      this.ah.value = String(this.bright)
      axios
        .post('https://4f4owrwgp2.execute-api.us-east-1.amazonaws.com/v1/change', JSON.stringify(this.ah))
        .then(respons => {
          this.info = respons.data
          console.log(this.info)
        })
    },
    ono() {
      this.ah.method = 'power'
      this.$store.state.onOff = this.switch1
      if (this.switch1 == true) {
        this.ah.value = 'on'
        axios
        .post('https://4f4owrwgp2.execute-api.us-east-1.amazonaws.com/v1/change', JSON.stringify(this.ah))
        .then(respons => {
          this.info = respons.data
          console.log(this.info)
        })
      } else {
        this.ah.value = 'off'
        axios
        .post('https://4f4owrwgp2.execute-api.us-east-1.amazonaws.com/v1/change', JSON.stringify(this.ah))
        .then(respons => {
          this.info = respons.data
          console.log(this.info)
        })
      }
    }
  },
  mounted(){
    this.switch1 = this.$store.state.onOff
  }
};
</script>

<style>
#Body {
  color: rgb(255, 255, 255);
  font-size: 20px;
}
</style>

    // on: {
    //   method: 'power',
    //   value: 'on',
    //   pass: 'okokokok'
    // },
    // off: {
    //   method: 'power',
    //   value: 'off',
    //   pass: 'okokokok'
    // },
    // colorR: {
    //   method: 'ctrl',
    //   value: this.colorRgb,
    //   pass: 'okokokok'
    // }
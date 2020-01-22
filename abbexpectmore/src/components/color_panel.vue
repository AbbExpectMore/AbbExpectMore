<template>
  <!-- <v-row align="start" justify="space-around" no-gutters> -->
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
              :loading="this.$store.state.loading"
            ></v-switch>
          </v-row>

          <v-row align="start" justify="space-around" no-gutters v-if="mode == 'Brightness'">
              <v-slider 
              color="#f3952d"
              :label='this.bright  + "%"'
              inverse-label= True
              v-model="bright">
              </v-slider>
          </v-row>
          <v-row align="start" justify="space-around" no-gutters v-if="mode == 'Brightness'">
          <v-btn 
          @click="send()"
          :loading="this.$store.state.loading"
          >Update
          </v-btn>
          </v-row>
          <v-row v-if="mode == 'Color Wheel'" align="start" justify="space-around" no-gutters>
            <ColorPicker />
          </v-row>
          <v-alert :type="Alert_type" v-if="Alert">{{ Alert_text }}</v-alert>
      <!-- </v-flex> -->
    </v-col>
  <!-- </v-row> -->
</template>

<script>
// import ColorPicker from "vue-color-picker-wheel";
import { mapGetters } from "vuex";
import { mapActions } from "vuex";
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
          'onOff',
          'sends',
          'loading'
      ])
  },
  data: () => ({
    bright: 0,
    counter: 0,
    client: undefined,
    user: "abbexpectmore@gmail.com",
    pass: "ABBExpectMore2020",
    message: "",
    Alert: false,
    Alert_type: "warning",
    Alert_text: "Could not connect to broker :((",
    value: undefined,
    mode: 'Color Wheel',
    switch1: false,
    ch: 0,
    color: undefined,
    colorRgb: undefined,
    ah: {
      method: undefined, //brightness
      value: undefined
    }
  }),
  methods: {
    ...mapActions([
      'postRGB'
    ]),
    send() {
      this.$store.state.loading = true
      this.$store.state.sends.value = String(this.bright)
      this.$store.dispatch('postRGB')
    },
    ono() {
      this.$store.state.loading = true
      this.$store.state.onOff = this.switch1
      if (this.switch1 == true) {
        this.$store.state.sends.value = 'on'
        this.$store.dispatch('postRGB')
      } else {
        this.$store.state.sends.value = 'off'
        this.$store.dispatch('postRGB')
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
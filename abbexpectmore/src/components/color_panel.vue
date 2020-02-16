<template>
  <!-- <v-row align="start" justify="space-around" no-gutters> -->
    <v-col cols="auto">
      <!-- Normal Screen -->

          <v-radio-group dark v-model="mode" :mandatory="false">
            <v-radio label="On/Off" value="On/Off"></v-radio>
            <v-radio label="Color Wheel" value="Color Wheel"></v-radio>
            <v-radio label="Brightness" value="Brightness"></v-radio>
            <v-radio label="Modes" value="Modes"></v-radio>
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
        <!-- Modes -->
          <v-row align="start" justify="space-around" no-gutters v-if="mode == 'Modes'">
            <v-btn
            fab
            @click="send1()"
            class="ma-2">
              Rainbow
            </v-btn>
            <v-btn
            class="ma-2"
            fab
            @click="send2()">
              <v-icon>
                mdi-radioactive
              </v-icon>
            </v-btn>
          </v-row>

          <!-- Brightness -->
          <v-row align="start" justify="space-around" no-gutters v-if="mode == 'Brightness'">
              <v-slider 
              color="#f3952d"
              :label='this.bright  + "%"'
              inverse-label
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
import ColorPicker from '@/components/ColorPicker.vue'

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
          'loading',
          'modes'
      ])
  },
  data: () => ({
    bright: 0,
    counter: 0,
    value: undefined,
    mode: 'Color Wheel',
    switch1: false,
    ch: 0,
    color: undefined,
    colorRgb: undefined,
    ah: {
      method: undefined, //brightness
      value: undefined
    },
    inv: true,
  }),
  methods: {
    ...mapActions([
      'postRGB'
    ]),
    map(value, low1, high1, low2, high2) {
    return Math.round(low2 + (high2 - low2) * (value - low1) / (high1 - low1));
    },
    send1(){
      this.$store.state.sends.method = 'ctrl'
      this.$store.state.loading = true
      this.$store.state.sends.value = '(10,55,250)'
      this.$store.dispatch('postRGB')
    },
    send2(){
      this.$store.state.sends.method = 'ctrl'
      this.$store.state.loading = true
      this.$store.state.sends.value = '(9,55,250)'
      this.$store.dispatch('postRGB')
    },
    send() {
      this.$store.state.sends.method = 'ctrl'
      this.$store.state.loading = true
      let bri = this.map(this.bright, 0, 100, 0, 255)
      let bro = `(${bri},${bri},${bri})`
      // console.log(bro)
      this.$store.state.sends.value = bro
      // console.log(this.$store.state.sends.value)
      this.$store.dispatch('postRGB')
    },
    ono() {
      this.$store.state.sends.method = 'ctrl'
      this.$store.state.loading = true
      this.$store.state.onOff = this.switch1
      if (this.switch1 == true) {
        this.$store.state.sends.value = '(255,255,255)'
        this.$store.dispatch('postRGB')
      } else {
        this.$store.state.sends.value = '(0,0,0)'
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
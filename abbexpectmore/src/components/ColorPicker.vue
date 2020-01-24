<template>
  <div>
    <!-- <span class="white--text">{{color}}</span> -->
    <color-picker @change="yes" variant="persistent" v-bind="color" @input="onInput" ></color-picker>
    <v-row align="start" justify="space-around">
      <v-slider color="#f3952d" v-model='color.luminosity'></v-slider>
    </v-row>
    <v-row align="start" justify="space-around">
      <v-slider color="#f3952d" v-model="color.saturation"></v-slider>
    </v-row>

    <p>Use the color wheel to pick a color and then
      use the sliders to chose saturation and luminosity.</p>

    <v-row align="start" justify="space-around">
      <v-btn 
      dark 
      style="transform: scale(1.25)" 
      class="mt-4" 
      @click="yes()"
      :loading="this.$store.state.loading"
      >Update</v-btn>
    </v-row>
  </div>
</template>

<script>
import ColorPicker from '@radial-color-picker/vue-color-picker'
import { mapGetters } from "vuex";
import { mapActions } from 'vuex';
import axios from 'axios'

export default {
  components: {
    ColorPicker
  },
  computed: {
    ...mapGetters([
      'sends',
      'loading'
    ])
  },
  data: () => ({
    color: { 
      hue: 0,
      saturation: 100,
      luminosity: 50,
      alpha: 1
    },
    rgb: undefined,
    title: 'click'
  }),
  methods: {
    ...mapActions([
      'postRGB',
      'log_out'
    ]),
    colorwell(){
      // console.log('test')
    },
    onInput(hue){
      this.color.hue = hue;
    },
    check_lock(){
      axios
        .get('https://4f4owrwgp2.execute-api.us-east-1.amazonaws.com/v1/')
        .then(respons => {
          var info = respons.data
          this.$store.state.locked = info.locked
          // console.log(info.locked)
        })
    },
    yes(){
      this.$store.state.loading = true;
      this.check_lock()
      this.rgb = this.HSLToRGB(this.color.hue, this.color.saturation, this.color.luminosity)
      this.$store.state.sends.value = this.rgb
      this.$store.dispatch('postRGB')
    },
    HSLToRGB(h,s,l) {
  // Must be fractions of 1
  s /= 100;
  l /= 100;

  let c = (1 - Math.abs(2 * l - 1)) * s,
      x = c * (1 - Math.abs((h / 60) % 2 - 1)),
      m = l - c/2,
      r = 0,
      g = 0,
      b = 0;

      if (0 <= h && h < 60) {
    r = c; g = x; b = 0;
  } else if (60 <= h && h < 120) {
    r = x; g = c; b = 0;
  } else if (120 <= h && h < 180) {
    r = 0; g = c; b = x;
  } else if (180 <= h && h < 240) {
    r = 0; g = x; b = c;
  } else if (240 <= h && h < 300) {
    r = x; g = 0; b = c;
  } else if (300 <= h && h < 360) {
    r = c; g = 0; b = x;
  }
  r = Math.round((r + m) * 255);
  g = Math.round((g + m) * 255);
  b = Math.round((b + m) * 255);

  return "(" + r + "," + g + "," + b + ")";
},
  }
};
</script>

<style>
  @import '~@radial-color-picker/vue-color-picker/dist/vue-color-picker.min.css';  
</style>


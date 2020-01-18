<template>
  <div>
    <!-- <span class="white--text">{{color}}</span> -->
    <color-picker transparent v-bind="color" @input="onInput" ></color-picker>
    <v-btn class="white--text" @click="yes()">{{rgb}}</v-btn>
    <span class="white--text">{{this.color.hue}}</span>
  </div>
</template>

<script>
import ColorPicker from '@radial-color-picker/vue-color-picker' 

export default {
  components: {
    ColorPicker
  },
  data: () => ({
    color: { 
      hue: 50,
      saturation: 100,
      luminosity: 50,
      alpha: 1
    },
    rgb: undefined
  }),
  methods: {
    onInput(hue){
      this.color.hue = hue;
    },
    yes(){
      this.rgb = this.HSLToRGB(this.color.hue, this.color.saturation, this.color.luminosity)
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

  return "rgb(" + r + "," + g + "," + b + ")";
}


  }
};
</script>

<style>
  @import '~@radial-color-picker/vue-color-picker/dist/vue-color-picker.min.css';  
</style>


<template>
  <div>
    <!-- <span class="white--text">{{color}}</span> -->
    <color-picker variant="persistent" v-bind="color" @input="onInput"></color-picker>
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
  }),
  methods: {
    onInput(hue){
      this.color.hue = hue;
    }
  }
};
</script>

<style>
  @import '~@radial-color-picker/vue-color-picker/dist/vue-color-picker.min.css';
</style>


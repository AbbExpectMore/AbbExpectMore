<template>
  <v-row  align="start" justify="space-around" no-gutters>
    <v-col cols="auto">


      <!-- Page locked -->
      <v-card v-if="this.$store.state.locked" dark class="ma-4 grey darken-3 px-2">
      <v-tooltip bottom>
        <template v-slot:activator="{ on }">
          
          <h1 v-on="on">This page is locked</h1>
        </template>
        <span>To unlock, disable "Admin Control" under Admin (must be signed in)</span>
      </v-tooltip>
      </v-card>


      <!-- Normal Screen (Connected)-->
      <v-card width="337" v-if="!this.$store.state.locked" dark class="pa-4 ma-4 grey darken-3">
        <colorpanel/>
      </v-card>

    </v-col>
  </v-row>
</template>

<script>
import { mapGetters } from "vuex";

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
    value: undefined,
    mode: undefined,
    switch1: false,
    ch: 0,
    color: undefined,
    colorRgb: undefined,
    info: undefined,
    data: {
      method: "power",
      value: "on",
      pass: "okokokok"
    }
  })
};
</script>

<style>
#Body {
  color: rgb(255, 255, 255);
  font-size: 20px;
}
</style>

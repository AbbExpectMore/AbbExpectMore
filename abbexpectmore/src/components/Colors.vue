<template>
  <div id="Colors">
    <v-row v-if="loading" align="start" justify="space-around" no-gutters>
      <v-progress-circular
        :indeterminate="true"
        :rotate="0"
        :size="180"
        :value="0"
        :width="10"
        color="light-blue"
        class="ma-12"
      ></v-progress-circular>
    </v-row>
    <v-row v-if="!loading" align="start" justify="space-around" no-gutters>
      <v-card dark class="ma-4 pb-3 grey darken-3 px-2">
        <h2 class="grey--text text--lighten-1 text-center">Last picked colors</h2>
        <v-row align="start" justify="space-around" no-gutters>
          <v-btn
            fab
            v-for="(color, i) in all_vals"
            :key="i"
            class="ma-1"
            :color="all_vals[i]"
            @click="send(all_vals[i])"
          ></v-btn>
        </v-row>
      </v-card>
    </v-row>
  </div>
</template>

<script>
import axios from "axios";
import { mapGetters } from "vuex";

export default {
  name: "Colors",
  data: () => ({
    values: "Hello",
    all_vals: [],
    loading: true,
    go: true
  }),
  computed: {
    ...mapGetters(["modes"])
  },
  methods: {
    send(color) {
      color = color.replace("rgb", "");
      this.$store.state.sends.value = color;
      this.$store.dispatch("postRGB");
    },
    test() {
      axios
        .get("https://4f4owrwgp2.execute-api.us-east-1.amazonaws.com/v1/all")
        .then(respons => {
          var info = respons.data;
          info = info.reverse();
          for (let i = 0; i < info.length; i++) {
            this.go = true;
            if (this.all_vals.length >= 10) {
              break;
            } else if (this.all_vals.length != 0) {

              let valu = info[i][0].replace("(", "");
              valu = valu.replace(")", "");
              let val = valu.split(",");
              if (val[0] == val[1] && val[2]) {
                null;
              } else {
                if (this.all_vals.length < 10) {
                  this.$store.state.modes.forEach(element => {
                    if (info[i][0] == element.color) {
                      this.go = false;
                    }
                  });
                  this.all_vals.forEach(element => {
                    if ("rgb" + info[i][0] == element) {
                      this.go = false;
                    }
                  });
                  if (this.go) {
                    this.all_vals.push("rgb" + info[i][0]);
                  }
                }
              }
            } else {
              let valu = info[i][0].replace("(", "");
              valu = valu.replace(")", "");
              let val = valu.split(",");

              this.$store.state.modes.forEach(element => {
                if (info[i][0] == element.color) {
                  this.go = false;
                }
              });
              this.all_vals.forEach(element => {
                if ("rgb" + info[i][0] == element) {
                  this.go = false;
                }
              });
              if (val[0] == val[1] && val[2]) {
                this.go = false;
              } 
              if (this.go) {
                this.all_vals.push("rgb" + info[i][0]);
              }
              
            }
          }

          this.loading = false;
        });
    }
  },
  created() {},
  mounted() {
    this.test();
  }
};
</script>

<style scoped>
</style>
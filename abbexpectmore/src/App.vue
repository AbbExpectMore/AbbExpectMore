<template >
  <v-app id="background">
    <toolbar />
    <v-content>

      <v-row align="start" justify="space-around" no-gutters>

      <!-- Actual app, all views and content -->
      <v-fade-transition mode="out-in">
        <router-view/>
      </v-fade-transition>
      </v-row>

    </v-content>
  </v-app>
</template>

<script>
import axios from 'axios'
import { mapGetters } from 'vuex'

export default {
  components: {
    toolbar: () => import("./components/toolbar.vue"),
  },
  data: () => ({
    color: {
      hue: 50,
      saturation: 100,
      luminosity: 50,
      alpha: 1
    },
  }),
  computed: {
    ...mapGetters([
      'locked'
    ])
  },
  created(){
    axios
      .get('https://4f4owrwgp2.execute-api.us-east-1.amazonaws.com/v1/')
      .then(respons => {
        var info = respons.data
        // console.log(info)
        this.$store.state.locked = info.locked
      })
  },
  methods: {
  }
};
</script>

<style>
  #background{
    background-image: url('https://images.unsplash.com/photo-1513346940221-6f673d962e97?ixlib=rb-1.2.1&ixid=eyJhcHBfaWQiOjEyMDd9&auto=format&fit=crop&w=1050&q=80');
  background-position: center; /* Center the image */
  background-repeat: no-repeat; /* Do not repeat the image */
  background-size: cover; /* Resize the background image to cover the entire container */
  }
</style>
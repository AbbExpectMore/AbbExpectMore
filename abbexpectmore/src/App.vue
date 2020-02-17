<template >
  <v-app id="background">
    <!-- Rendering toolbar -->
    <toolbar />
    <v-content>

      <v-row align="start" justify="space-around" no-gutters>
      <v-fade-transition mode="out-in">
        <!-- Triggering router view -->
        <router-view/>
      </v-fade-transition>
      <!-- Running snackbar comp -->
        <snackbar/>
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
    snackbar: () => import("./components/snackbar.vue"),
  },
  data: () => ({
    //Color wheel vairables
    color: {
      hue: 50,
      saturation: 100,
      luminosity: 50,
      alpha: 1
    },
  }),
  computed: {
    ...mapGetters([
      'locked',
      'last_val',
      'onOff',
      // 'client'
    ])
  },
  created(){
    this.check();
    //Interval for regualrly checking if page has been locked
    setInterval(() => {
      this.check()
    }, 2000)
  },
  //Check if locked whenever page is reloaded
  updated(){
    axios
      .get('https://4f4owrwgp2.execute-api.us-east-1.amazonaws.com/v1/')
      .then(respons => {
        var info = respons.data
        this.$store.state.locked = info.locked
      })
  },
  mounted(){
    
    },
  methods: {
    //Check if page is locked
    check(){
      axios
      .get('https://4f4owrwgp2.execute-api.us-east-1.amazonaws.com/v1/')
      .then(respons => {
        var info = respons.data
        this.$store.state.locked = info.locked
        this.$store.state.last_val = info.Last_val
          if (this.$store.state.last_val == '(0,0,0)'){
            this.$store.state.onOff = false
          }else{
            this.$store.state.onOff = true
          }
          this.once = true
        
      })
    }
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
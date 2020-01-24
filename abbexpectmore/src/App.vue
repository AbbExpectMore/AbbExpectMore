<template >
  <v-app id="background">
    <toolbar />
    <v-content>
      <!-- rainbow mode -->
<!-- 10,55,250 -->

      <v-row align="start" justify="space-around" no-gutters>

      <!-- Actual app, all views and content -->
      <!-- <v-btn :disabled=connected @click="connect()">Connect</v-btn>
      <v-btn :disabled=subscribed @click="subscribe()">subscribe</v-btn>
      <v-btn @click="send()">Send</v-btn> -->
      <v-fade-transition mode="out-in">
        <router-view/>
      </v-fade-transition>
      </v-row>

    </v-content>
  </v-app>
</template>

<script>
import axios from 'axios'
import { mapGetters, mapActions } from 'vuex'
var mqtt = require('mqtt'),
  url = require('url')

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
    connected: false,
    client: undefined,
    user: "abbexpectmore@gmail.com",
    pass: "Hej",
    message: true,
    once: false,
    topic: 'abbexpectmore@gmail.com/lock',
    topic1: 'abbexpectmore@gmail.com/l',
    last_payload: false,
    subscribed: false
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
    // this.connect()
    // this.subscribe()
    setInterval(() => {
      this.check()
    }, 20000)
  },
  updated(){
    axios
      .get('https://4f4owrwgp2.execute-api.us-east-1.amazonaws.com/v1/')
      .then(respons => {
        var info = respons.data
        this.$store.state.locked = info.locked
        // console.log(info.locked)
      })
  },
  mounted(){
    
    },
  methods: {
    send() {
      let msg = String(this.message)
      this.client.publish(this.topic, msg);
      this.last_payload = msg
      this.message = !this.message
    },
    subscribe(){
      this.client.subscribe(this.topic, function(err, granted){
        console.log(granted)
      })
      this.subscribed = true
    },
    con_sub(){
      
    },
    // ...mapActions([
    //   'locked',
    // ]),
    connect() {
      var mqtt_url = "maqiatto.com";
      var url = "mqtt://" + mqtt_url;
      var options = {
        port: 8883,
        clientId:
          "mqttjs_" +
          Math.random()
            .toString(16)
            .substr(2, 8),
        username: this.user,
        password: this.pass
      };
      // user = this.options.username
      // pass = this.options.password
      console.log("connecting");
      this.client = mqtt.connect(url, options);
      console.log("connected?");
      this.client
        .on("error", function(error) {
          console.log("no");
          this.Alert = true;
          this.connected = false;
          console.log(this.Alert, this.connected);
        })
        .on("close", function(error) {
          console.log("no");
          this.Alert = true;
          this.connected = false;
        });
      this.$store.state.client = this.client
      this.connected = true;
    },
    check(){
      axios
      .get('https://4f4owrwgp2.execute-api.us-east-1.amazonaws.com/v1/')
      .then(respons => {
        var info = respons.data
        this.$store.state.locked = info.locked
        // console.log(info.locked)
        this.$store.state.last_val = info.Last_val
        if (!this.once){
          if (this.$store.state.last_val == '(0,0,0)'){
            this.$store.state.onOff = false
          }else{
            this.$store.state.onOff = true
          }
          this.once = true
        }
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
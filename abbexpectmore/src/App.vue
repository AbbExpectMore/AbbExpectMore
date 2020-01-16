<template>
  <v-app>
    <toolbar />
    <v-content class="grey darken-4">
      <v-fade-transition mode="out-in">
        <!-- <v-btn v-if="!mode" @click="connect()"></v-btn> -->
        <router-view/>
      </v-fade-transition>
    </v-content>
  </v-app>
</template>

<script>
import { connect } from 'mqtt';
import { mapActions } from 'vuex';

var mqtt = require("mqtt"),
  url = require("url");

export default {
  components: {
    toolbar: () => import("./components/toolbar.vue")
  },
  data: () => ({
    connected: false,
    client: undefined,
    user: "abbexpectmore@gmail.com",
    pass: "ABBExpectMore2020",
    message: "",
    Alert: false,
    Alert_type: "warning",
    Alert_text: "Could not connect to broker :((",
    value: undefined,
    mode: false,
  }),
  methods: {
    ...mapActions([
      'conn_fail',
      'connected'
    ]),
    run() {
      console.log('Who')
      this.$store.dispatch('connected')
    },
    connect() {
      console.log('Connecting')
      //mqtt://maqiatto.com
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
      this.client = mqtt.connect('mqtt://maqiatto.com', options);
      console.log("connected?");

      this.client
        .on("error", function(error) {
          console.log("no");
          // this.Alert = true;
          this.connected = false
          // console.log(this.Alert, this.connected);
        })
        .on("close", function(error) {
          console.log("no");
          // this.Alert = true;
          this.connected = false
        });
      this.connected = true
      this.mode = true
      console.log('Connected!')
    },
  },
  mounted(){
    console.log('mounting')
  }
};
</script>


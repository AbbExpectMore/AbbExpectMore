<template>
  <div id="test2">
    <v-row align="start" justify="space-around" no-gutters>
      <v-card v-if="!this.$store.state.ad_stat" class="ma-7" dark>
        <v-form class="ma-5 pa-4" v-model="form">
          <v-text-field
            v-on:keyup.enter="login"
            dark
            v-model="creds.user"
            label="Username"
            required
          ></v-text-field>
          <v-text-field
            v-on:keyup.enter="login"
            dark
            v-model="pass"
            label="Password"
            type="password"
            required
          ></v-text-field>
          <v-row align="start" justify="space-around" no-gutters>
            <v-btn
              :v-if="!this.$store.state.ad_stat"
              :disabled="(pass == undefined) || (creds.user == undefined)"
              :loading="this.$store.state.loading"
              @click="login()"
            >Sign in</v-btn>
          </v-row>
        </v-form>
        <v-alert
          v-if="!this.$store.state.ad_stat && this.$store.state.tried_once"
          class="mx-4"
          color="#f3952d"
          type="warning"
          :dismissible="true"
        >Login Failed</v-alert>
      </v-card>

      <v-card width="337" v-if="this.$store.state.ad_stat" class="mt-2 pt-3 px-10" dark>
        <v-radio-group v-model="option">
          <v-radio label="Lock" value="Lock"></v-radio>
          <v-radio label="Color Options" value="Color Options"></v-radio>
          <v-radio label="Timer" value="Timers"></v-radio>
        <v-radio-group v-if="option == 'Timers'" color="white--text" v-model="optionTime">
            <v-radio label="Timer" value="Timer"></v-radio>
            <v-radio label="Set time" value="Set time"></v-radio>
          </v-radio-group>
        </v-radio-group>
      </v-card>
    </v-row>

    <v-row align="start" justify="space-around" no-gutters>
      <v-card
        width="337"
        v-if="this.$store.state.ad_stat && this.option == 'Lock'"
        class="mt-2 pt-3 px-10"
        dark
      >
        <v-row align="start" justify="space-around" no-gutters>
          <v-switch
            @change="lockIt()"
            color="#f3952d"
            v-model="switch_admin"
            style="transform: scale(1.5)"
            label="Lock"
          ></v-switch>
        </v-row>
      </v-card>
      <v-card
        width="337"
        v-if="this.$store.state.ad_stat && this.option == 'Color Options'"
        class="ma-7 py-2 px-10"
        dark
      >
        <colorpanel />
      </v-card>

      <!-- <v-card width="337" v-if="this.$store.state.ad_stat && this.option == 'Timers'" class="mt-2 pt-3 px-10" dark> -->
        <v-card
        dark
        class="mt-3"
        color="grey darken-3"
        width="337"
        v-if="this.$store.state.ad_stat && this.option == 'Timers' && info2 && optionTime == 'Timer'">
        <v-row align="start" justify="space-around" no-gutters>
          <p class="ma-2">To set a timeout turn the clock dials to a the amount of time you want to wait (max 24h), then press 'Set Timer' and wait.</p>
          <v-btn width="337" @click="info2 = false">
            <v-icon>
              mdi-close
            </v-icon>
          </v-btn>
    </v-row>
        </v-card>
        <v-card
        dark
        class="mt-3"
        color="grey darken-3"
        width="337"
        v-if="this.$store.state.ad_stat && this.option == 'Timers' && info1 && optionTime == 'Set time'">
      <v-row align="start" justify="space-around" no-gutters>
          <p class="ma-2">To set a time turn the clock dials to a the time you want it to turn off, then press 'Set Time' and wait.</p>
          <v-btn width="337" @click="info1 = false">
            <v-icon>
              mdi-close
            </v-icon>
          </v-btn>
    </v-row>
        </v-card>
    </v-row>

    <v-row align="start" justify="space-around" no-gutters>
      <v-card
        class="mt-3"
        color="grey darken-3"
        width="337"
        v-if="this.$store.state.ad_stat && this.option == 'Timers' && optionTime == 'Timer'"
      >
        <v-time-picker
        format="24hr"
          color="grey darken-3"
          v-model="time"
          width="337"
          type="month"
        ></v-time-picker>
        <!-- <v-btn width="168" color="green" @click="setStart">Set Start</v-btn> -->
        <!-- <v-btn width="168" color="red">Set Stop</v-btn> -->
        <v-btn width="337" color="red" @click="setTimer">Set Timer</v-btn>
      </v-card>


      

      <v-card
        class="mt-3"
        color="grey darken-3"
        width="337"
        v-if="this.$store.state.ad_stat && this.option == 'Timers' && optionTime == 'Set time'"
      >
        <v-time-picker
        format="24hr"
          color="grey darken-3"
          v-model="time1"
          width="337"
        ></v-time-picker>
        <!-- <v-btn width="168" color="green" @click="setStart">Set Start</v-btn> -->
        <!-- <v-btn width="168" color="red">Set Stop</v-btn> -->
        <v-btn width="337" color="red" @click="setTime">Set Time</v-btn>
      </v-card>
      <!-- </v-card> -->

    </v-row>
  </div>
</template>

<script>
import { mapGetters } from "vuex";
import { mapActions } from "vuex";
import sha256 from "sha256";
import axios from "axios";

export default {
  components: {
    colorpanel: () => import("@/components/color_panel.vue")
  },
  computed: {
    ...mapGetters(["ad_stat", "locked", "client", 'sends', 'res', 'info'])
  },
  data: () => ({
    pass: undefined,
    switch_admin: false,
    passcryp: undefined,
    creds: {
      user: undefined,
      pass: undefined
    },
    form: false,
    tried_once: false,
    option: "Lock",
    optionTime: '',
    time: '00:00',
    time1: '00:00',
    info1: true,
    info2: true,
    mess: 'Ops?',
    color: 'grey',
    timeout: 3000,
  }),
  methods: {
    ...mapActions(["cred_check", "log_out", "lock", 'postRGB']),
    enter() {
      // console.log('Hello')
    },
    setStart() {
      console.log(this.time);
      var today = new Date();
      var date = today.getHours() + ":" + today.getMinutes();
      console.log(date);
      var unix = Math.round(+new Date() / 1000);
      console.log("unix " + unix); //WORK HERE THOOOOOOOOOOOOOOOOO
    },
    setTimer(){
      this.$store.state.sends.method = 'timeout'
      var today = new Date
      var now = Math.round(+new Date() / 1000);
      var timer = this.time.split(':')
      var stop = Math.round(+new Date()/1000) + timer[0]*3600 + timer[1]*60;
      stop = stop - now;
      this.$store.state.sends.value = stop.toString();
      this.$store.dispatch('postRGB')
    },
    setTime(){
      this.$store.state.sends.method = 'timeout'
      var now = new Date;
      var unixNow = Math.round(+new Date() / 1000);
      var timeSplit = this.time1.split(':');
      var unixThen = Math.round(+new Date(now.getFullYear(), now.getMonth(), now.getDate(),timeSplit[0],timeSplit[1],0) /1000);
      if(unixNow > unixThen){
        unixThen = Math.round(+new Date(now.getFullYear(), now.getMonth(), now.getDate()+1,timeSplit[0],timeSplit[1],0) /1000);
      }
      var unixSend = unixThen - unixNow;
      this.$store.state.sends.value = unixSend.toString();
      this.$store.dispatch('postRGB')
    },
    send() {
      let msg = "1";
      this.$store.state.client.publish(this.topic, msg);
    },
    loggo() {
      this.creds.user = undefined;
      this.pass = undefined;
      this.$store.dispatch("log_out");
    },
    lockIt() {
      this.$store.dispatch("lock");
      this.switch_admin = this.$store.state.locked;
    },
    login() {
      if (this.pass != undefined) {
        this.$store.state.loading = true;
        this.creds.pass = sha256(this.pass);
        this.$store.dispatch("cred_check", JSON.stringify(this.creds));
      }
    }
  },
  mounted() {
    this.switch_admin = this.$store.state.locked;
  }
};
</script>

<style>
</style>
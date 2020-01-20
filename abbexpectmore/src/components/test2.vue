<template>
  <div id="test2">
    <v-row align="start" justify="space-around" no-gutters>
      <v-card v-if="!this.$store.state.ad_stat" class="ma-7" dark>
      <v-form class="ma-5 pa-4">
        <v-text-field dark v-model="creds.user" label="Username" required></v-text-field>
        <v-text-field dark v-model="pass" label="Password" type="password" required></v-text-field>
        <v-row align="start" no-gutters>
          <v-btn v-if="!this.$store.state.ad_stat" @click="login()">Sign in</v-btn>
        </v-row>
      </v-form>
      </v-card>
      <v-card v-if="this.$store.state.ad_stat" class="ma-7 py-2 px-10" dark>
        <v-row  align="start" justify="space-around" no-gutters>
        <v-switch @change="lockIt()" color="#f3952d" v-model="switch_admin" style="transform: scale(1.25)" label="Admin Control"></v-switch>
        </v-row>
          <colorpanel v-if="this.$store.state.locked"/>
        </v-card>
    </v-row>
  </div>
</template>

<script>
import { mapGetters } from "vuex";
import { mapActions } from "vuex";
import sha256 from 'sha256';
import axios from 'axios';

export default {
    components: {
      colorpanel: () => import("@/components/color_panel.vue"),
    },
  computed: {
      ...mapGetters([
          'ad_stat',
          'locked'
      ]),
  },
  data: () => ({
      pass: undefined,
      switch_admin: false,
      passcryp: undefined,
      creds: {
        user: undefined,
        pass: undefined
      },
  }),
  methods: {
      ...mapActions([
          'cred_check',
          'log_out',
          'lock'
      ]),
      loggo(){
          this.creds.user = undefined
          this.pass = undefined
          this.$store.dispatch('log_out')
      },
      lockIt(){
        this.$store.dispatch('lock')
        this.switch_admin = this.$store.state.locked
      },
      login(){
        this.creds.pass = sha256(this.pass)
        this.$store.dispatch('cred_check', JSON.stringify(this.creds))
      }
  },
  mounted(){
    this.switch_admin = this.$store.state.locked
  }
};
</script>

<style>
</style>
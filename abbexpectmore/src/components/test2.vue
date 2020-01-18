<template>
  <div id="test2">
    <v-row align="start" justify="space-around" no-gutters>
      <v-card v-if="!this.$store.state.ad_stat" class="ma-7" dark>
      <v-form class="ma-5 pa-4">
        <v-text-field dark v-model="user" label="Username" required></v-text-field>
        <v-text-field dark v-model="pass" label="Password" type="password" required></v-text-field>
        <v-row align="start" no-gutters>
          <v-btn v-if="!this.$store.state.ad_stat" @click="cred_check(user+pass)">Sign in</v-btn>
          <!-- <v-btn>{{this.$store.state.ad_stat}}</v-btn> -->
        </v-row>
      </v-form>
      </v-card>
      <v-card v-if="this.$store.state.ad_stat" class="ma-7 py-2 px-10" dark>
        <v-row  align="start" justify="space-around" no-gutters>
        <v-switch @change="lock()" color="#f3952d" v-model="this.$store.state.locked" style="transform: scale(1.25)" label="Admin Controll"></v-switch>
        </v-row>
        <colorpanel v-if="this.$store.state.locked"/>
        </v-card>
    </v-row>
  </div>
</template>

<script>
import { mapGetters } from "vuex";
import { mapActions } from "vuex";
export default {
    components: {
      colorpanel: () => import("@/components/color_panel.vue")
    },
  computed: {
      ...mapGetters([
          'ad_stat',
          'locked'
      ]),
  },
  data: () => ({
      user: undefined,
      pass: undefined,
      switch_admin: false,
  }),
  methods: {
      ...mapActions([
          'cred_check',
          'log_out',
          'lock'
      ]),
      loggo(){
          this.user = undefined
          this.pass = undefined
          this.$store.dispatch('log_out')
      }
  }
};
</script>

<style>
</style>
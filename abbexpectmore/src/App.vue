<template>
  <v-app>
    <toolbar />
    <v-content class="grey darken-4">

      <v-row align="start" justify="space-around" no-gutters>

        <!-- for visual lamp/render a mirror -->
      <!-- <v-card dark class="grey darken-3 ma-4">
        <v-icon size="100">
          mdi-lightbulb-outline
        </v-icon>
      </v-card> -->

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


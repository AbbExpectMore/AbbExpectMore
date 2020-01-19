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
  mounted(){
    console.log('mounting')
  },
  methods: {
  }
};
</script>


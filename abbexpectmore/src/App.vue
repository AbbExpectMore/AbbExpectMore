<template>
  <v-app>
    <v-app-bar
      app
      color="primary"
      dark
    >
      <div class="d-flex align-center">
        <v-img
          alt="Vuetify Logo"
          class="shrink mr-2"
          contain
          src="https://avatars3.githubusercontent.com/u/57906616?s=400&u=efdb1bd1861ee999838490bb1629091b155ff437&v=4"
          transition="scale-transition"
          width="40"
        />

        <span>
          Lamp Control
        </span>
      </div>

      <v-spacer></v-spacer>

      <v-btn
        href="/Help"
        target="_blank"
        text
      >
        <span class="mr-2">Help</span>
        <v-icon>mdi-open-in-new</v-icon>
      </v-btn>
    </v-app-bar>

    <v-content>
      <ControlLights/>
    </v-content>
  </v-app>
</template>

<script>
import ControlLights from './components/ControlLights';

export default {
  name: 'App',

  components: {
    ControlLights,
  },

  data: () => ({
    //
  }),
};
</script>

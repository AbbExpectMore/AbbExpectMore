<template>
  <div>
    <v-toolbar dark>
      <v-toolbar-title>
        <v-img
          alt="Vuetify Logo"
          class="shrink mr-2"
          contain
          src="https://avatars3.githubusercontent.com/u/57906616?s=400&u=efdb1bd1861ee999838490bb1629091b155ff437&v=4"
          transition="scale-transition"
          width="40"
        />
        </v-toolbar-title>

      <v-spacer></v-spacer>

      <v-toolbar-items>
        <v-btn v-for="(link, i) in links" :key="i" :to="link.path">{{link.name}}</v-btn>
      </v-toolbar-items>
    </v-toolbar>
  </div>
</template>

<script>
import paths from "@/router/paths";

export default {
  data: () => ({}),
  computed: {
    links() {
      return paths;
    }
  }
};
</script>
<template>
  <v-app>
    <toolbar />
    <v-content class="grey darken-4">
      <v-fade-transition mode="out-in">
        <router-view />
      </v-fade-transition>
    </v-content>
  </v-app>
</template>

<script>
export default {
  components: {
    toolbar: () => import("./components/toolbar.vue")
  }
};
</script>


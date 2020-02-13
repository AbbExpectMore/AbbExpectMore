<template>
    <!-- Vuetify snackbar for user response -->
  <div>
    <v-row align="start" justify="space-around" no-gutters>
      <v-snackbar width='200' :color="$store.state.snackColor" v-model="$store.state.snackShow" :timeout='timeout'>
        {{$store.state.snackMessage}}
      </v-snackbar>
    </v-row>
  </div>
</template>

<script>
import { mapGetters } from "vuex";

export default {
  computed: {
      ...mapGetters(['snackShow', 'snackMessage', 'snackColor'])
  },
  data: () => ({
      timeout: 1000,
  })
};
</script>
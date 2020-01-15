<template>
  <div id="Admin">
    <v-form class="ma-5 pa-4">
      <v-text-field dark v-model="user" label="Username" required></v-text-field>
      <v-text-field dark v-model="pass" label="Password" type="password" required></v-text-field>
    </v-form>
  </div>
</template>

<script>
import { mapState, mapGetters, mapActions } from 'vuex'
export default {
  computed: {
    ...mapGetters([
      
    ])
  },
  data: () => ({
    user: undefined,
    pass: undefined
  }),
  methods:{
    ...mapActions([

    ])
  }
}
</script>

<style>
#Body {
  color: rgb(255, 255, 255);
  font-size: 20px;
}
</style>

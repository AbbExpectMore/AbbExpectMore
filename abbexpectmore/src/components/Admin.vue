<template>
  <div id="Admin">
    <v-row>
    <v-form class="ma-5 pa-4">
      <v-text-field dark  label="Username" required></v-text-field>
      <v-text-field dark v-model="pass" label="Password" type="password" required></v-text-field>
    </v-form>
    </v-row>
  </div>
</template>

<script>
import { mapGetters } from 'vuex'
import { mapActions } from 'vuex'
export default {
  // computed: {
  //   ...mapGetters([
      
  //   ])
  // },
  data: () => ({
    user: undefined,
    pass: undefined
  }),
  // methods:{
  //   ...mapActions([

  //   ])
  // }
}
</script>

<style>
#Body {
  color: rgb(255, 255, 255);
  font-size: 20px;
}
</style>

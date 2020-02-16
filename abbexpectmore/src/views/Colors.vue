<template>
  <v-row align="start" justify="space-around" no-gutters>
      <Colors/>
  </v-row>
</template>

<script>

export default {
  components: {
    Colors: () => import("@/components/Colors.vue")
  },
}
</script>

<style>

#Body {
  color: rgb(255, 255, 255);
  font-size:20px;
}

</style>

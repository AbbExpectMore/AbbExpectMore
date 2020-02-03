<template>
  <v-row align="start" justify="space-around" no-gutters>
    <v-progress-circular
        :indeterminate="true"
        :rotate="0"
        :size="180"
        :value="0"
        :width="10"
        color="light-blue"
        class ="ma-12"
      ></v-progress-circular>
  </v-row>
</template>

<style>

#Body {
  color: rgb(255, 255, 255);
  font-size:20px;
}

</style>

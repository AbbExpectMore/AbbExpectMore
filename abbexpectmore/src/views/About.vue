<template>
  <v-row align="start" justify="space-around" no-gutters>
    <v-card class="ma-4 grey darken-4" max-width=400>
  <v-row align="start" justify="space-around" no-gutters>
    <!-- <v-card class="mx-auto grey darken-4"> -->
    <h1 class="ma-4 grey--text text--lighten-1 text-center">ABB Expect More</h1>
    <h3 class="grey--text text--lighten-1 text-center">This website and the lamp it controls was created as a school project by students attending ABB Industrigymnasium, 2020.
      <br> <br> The purpose of this project was to construct a "smart" lamp and to control it in a smart way using a website. With this website, it is possible to control the color and brightness as well as the on-state with a simple on/off switch.
      <br> <br> It is also possible lock the lamp’s state by logging in as an administrator. By locking it only people with the correct username and password will be able to edit the lamp's values.
      <br> <br>
    </h3>

    <v-col cols="12">
      <v-row align="start" justify="space-around" no-gutters>
        <v-img
          alt="ABBgym Logo"
          class="shrink ma-2 pa-2"
          contain
          src="@/assets/logo.png"
          transition="scale-transition"
          minWidth="300"
          maxWidth="300"
          position="center center"
        />
      </v-row>
    </v-col>

    <!-- </v-card> -->
  </v-row>
  </v-card>
  </v-row>
</template>

<style scoped>
#Body {
  color: rgb(255, 255, 255);
  font-size: 20px;
}
.centered {
  display: block;
  width: 90%;
  max-width: 400px;
  margin: 0 auto;
}
h1{
  color: grey;
  text-decoration: underline;
}
</style>



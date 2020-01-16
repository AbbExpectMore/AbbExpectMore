<template>
  <v-container>
    <v-layout text-center wrap>
      <v-flex xs12>
        <v-layout justify-center id="Body">
          <v-img
          alt="Expetrum Logo"
          class="shrink mr-2"
          contain
          src="@/assets/logo.png"
          transition="scale-transition"
          width="250"
        />
        <!-- <h1>
            This is an about page
        </h1> -->
        </v-layout>
      </v-flex>
    </v-layout>
  </v-container>
</template>

<style>

#Body {
  color: rgb(255, 255, 255);
  font-size:20px;
}

</style>

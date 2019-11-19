<template>
  <v-container class="black">
    <v-row
      class="mb-6"
      no-gutters
    >
      <v-col
        v-for="n in 4"
        :key="n"
      >
        <v-card
          class="pa-2"
          tile
          outlined
        >
          Opsi
        </v-card>
      </v-col>
    </v-row>

    <v-row no-gutters>
      <v-col
        v-for="n in 2"
        :key="n"
        :cols="n === 1 ? 8 : 4"
      >
        <v-card
          class="pa-2 black"
          tile
          outlined
        >
        <v-img
              alt="ABBgym Logo"
              class="shrink mr-2"
              contain
              src="@/assets/logo.png"
              transition="scale-transition"
              width="250"
            />
        </v-card>
      </v-col>
    </v-row>
  </v-container>
</template>

<style>

#Body {
  color: rgb(255, 255, 255);
  font-size:20px;
}

</style>

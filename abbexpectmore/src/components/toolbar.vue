<template>
  <div>
    <v-toolbar dark>
      <v-toolbar-title>
        <v-img
          href="/home"
          alt="Expectrum Logo"
          class="shrink mr-2"
          contain
          src="@/assets/expectrum.png"
          transition="scale-transition"
          width="100"
        />
      </v-toolbar-title>

      <v-spacer></v-spacer>


      <v-toolbar-items>
        <v-btn to="/home">
          <v-icon v-if="!this.$store.state.locked">
            mdi-lightbulb-outline
          </v-icon>
          <v-icon v-if="this.$store.state.locked">
            mdi-lightbulb-off-outline
          </v-icon>
        </v-btn>
        <v-btn to="/about">
        <v-icon>
          mdi-information-outline
        </v-icon>
        </v-btn>
        <v-btn v-if="this.$store.state.ad_stat" to="/admin">Admin</v-btn>
      </v-toolbar-items>

      <v-tooltip bottom v-if="!this.$store.state.ad_stat">
        <template v-slot:activator="{ on }">
          <v-btn to="/admin" class="ml-5" fab small color="#f3952d" @click="loggo()" dark v-on="on">
            <v-icon>
              mdi-account
            </v-icon>
          </v-btn>
        </template>
        <span>Sign In</span>
      </v-tooltip>

      <v-tooltip bottom v-if="this.$store.state.ad_stat">
        <template v-slot:activator="{ on }">
          <v-btn to="/admin" class="ml-5" fab small color="#f3952d" @click="loggo()" dark v-on="on">
            <v-icon>
              mdi-account-arrow-left
            </v-icon>
          </v-btn>
        </template>
        <span>Sign Out</span>
      </v-tooltip>
    </v-toolbar>
  </div>
</template>

<script>
import paths from "@/router/paths";
import { mapGetters } from "vuex";
import { mapActions } from "vuex";

export default {
  components: {},
  data: () => ({
    
  }),
  computed: {
    ...mapGetters([
      "ad_stat",
      "locked"
      ]),
    links() {
      return paths;
    }
  },
  methods: {
    ...mapActions(["log_out"]),
    loggo() {
      this.$store.dispatch("log_out");
    }
  }
};
</script>
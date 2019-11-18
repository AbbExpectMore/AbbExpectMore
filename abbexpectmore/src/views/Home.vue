<template>
  <div class="home">
    <ControlLights/>
  </div>
</template>

<script>
export default {
  components: {
    ControlLights: () => import("@/components/ControlLights.vue")
  }
};
</script>

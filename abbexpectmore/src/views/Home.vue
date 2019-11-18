<template>
  <div class="home">
    <img alt="Vue logo" src="../assets/logo.png">
    <ControlLights/>
  </div>
</template>

<script>
// @ is an alias to /src
import ControlLights from '@/components/ControlLights.vue'

export default {
  name: 'home',
  components: {
    ControlLights
  }
}
</script>

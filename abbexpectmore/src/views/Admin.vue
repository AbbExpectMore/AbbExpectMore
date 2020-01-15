<template>
  <div class="Admin">
    <test1 />
    <test2 />
  </div>
</template>

<script>
export default {
  name: 'Admin',
  components: {
    test1: () => import("@/components/test1.vue"),
    test2: () => import("@/components/test2.vue")
  },
  data(){
    return{
    }
  }
};
</script>
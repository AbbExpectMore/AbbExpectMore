<template>
  <div>
    <test2/>
  </div>
</template>

<script>
export default {
  name: 'Admin',
  components: {
    test2: () => import("@/components/test2.vue")
  },
  data(){
    return{
    }
  }
};
</script>
<template>
  <div>
    <!-- <Admin/> -->
    <test2/>
  </div>
</template>

<script>
export default {
  name: 'Admin',
  components: {
    // Admin: () => import("@/components/Admin.vue")
    test2: () => import("@/components/test2.vue")
  },
  data(){
    return{
    }
  }
};
</script>
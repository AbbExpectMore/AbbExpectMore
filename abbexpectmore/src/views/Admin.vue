<template>
  <div class="Admin">
    <Admin/>
  </div>
</template>

<script>
export default {
  name: 'Admin',
  components: {
    Admin: () => import("@/components/Admin.vue")
  },
  data(){
    return{
    }
  }
};
</script>
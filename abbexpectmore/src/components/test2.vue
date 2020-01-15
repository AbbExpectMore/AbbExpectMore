<template>
  <div id="test2">
      <h2 class="white--text">Test-2</h2>
      <ul>
          <li class="white--text" v-for="(product, i) in saleProducts" :key="i">
              <span>{{product.name}}</span>
              <span> €{{product.price}}</span>
          </li>
      </ul>
  </div>
</template>

<script>
export default {
    computed:{
        products(){
            return this.$store.state.products
        },
        saleProducts(){
            return this.$store.getters.saleProducts
        }
    },
    data(){
        return{
        }
        
    },
    methods: {
        click(){
            console.log(this.products)
        }
    }
};
</script>

<style>
    
</style>
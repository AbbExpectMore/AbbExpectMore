<template>
  <div id="test1">
      <h2 class="blue--text">Test-1</h2>
      <ul>
          <li class="blue--text" v-for="(product, i) in saleProducts" :key="i">
              <span>{{product.name}}</span>
              <span> €{{product.price}}</span>
          </li>
      </ul>
      <v-btn @click="reducePrice(10)">Reduce Price</v-btn>
  </div>
</template>

<script>
import {mapActions} from 'vuex'
import {mapGetters} from 'vuex'

export default {
    computed:{
        products(){
            return this.$store.state.products
        },
        ...mapGetters([
            'saleProducts'
        ])
    },
    data(){
        return{
        }
        
    },
    methods: {
        ...mapActions([
            'reducePrice'
        ])
    }
};
</script>

<style>

</style>
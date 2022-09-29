package org.appfloweb.keccak

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.TextView
import org.appfloweb.keccak.databinding.ActivityMainBinding
import java.util.*

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        binding.keccakTest.setOnClickListener {
            binding.sampleText.text = keccakTest()
        }
    }

    external fun keccakTest(): String

    companion object {
        // Used to load the 'keccak' library on application startup.
        init {
            System.loadLibrary("keccak")
        }
    }
}